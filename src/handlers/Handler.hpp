#ifndef HANDLER_HPP_

#define HANDLER_HPP_

#include "../HttpServerExceptions.hpp"
#include "../message/Request.hpp"
#include "../message/Response.hpp"
#include <iostream>

/*
 * Abstract class for handling HTTP requests and
 * outputting a Response object
 */
class Handler {
  public:
    virtual Response
    handleRequest(const Request &request)
    {
        try {
            processRequestLine(request);
            processHeaders(request);
            processRequestBody(request.getBody());
            constructResponseBody();
            return builder_.build();
        }
        catch (invalid_request const &e) {
            std::cerr << e.what() << std::endl;
            return builder_.reset()
                .setVersion(request.getVersion())
                .setStatusCode(StatusCode::BAD_REQUEST)
                .build();
        }
        catch (invalid_response const &e) {
            std::cerr << e.what() << std::endl;
            // Bad response construction on the server side

            return builder_.reset()
                .setVersion(request.getVersion())
                .setStatusCode(
                    StatusCode::INTERNAL_SERVER_ERROR)
                .build();
        }
        catch (std::exception const &e) {
            // Some unforeseen error
            // Fail gracefully
            return builder_.reset()
                .setVersion(request.getVersion())
                .setStatusCode(
                    StatusCode::INTERNAL_SERVER_ERROR)
                .build();
        }
    };

  protected:
    ResponseBuilder builder_{ Response::getBuilder() };
    // The following 4 methods plus maybe some extra ones
    // are called in handleRequest. Each method
    // incrementally gives more info to builder_
    virtual void processRequestLine(const Request &) = 0;
    virtual void processHeaders(const Request &) = 0;
    virtual void processRequestBody(const std::string &body)
        = 0;
    virtual void constructResponseBody() = 0;
};

#endif // !HANDLER_HPP_
