#ifndef HANDLER_HPP_

#define HANDLER_HPP_

#include "../HttpServerExceptions.hpp"
#include "../message/Request.hpp"
#include "../message/Response.hpp"
#include <iostream>
#include <ostream>
#include <stdexcept>
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
        catch (InvalidRequest const &e) {
            std::cout << e.what() << std::endl;
            return builder_.reset()
                .setVersion(request.getVersion())
                .setStatusCode(StatusCode::BAD_REQUEST)
                .build();
        }
    };

  protected:
    ResponseBuilder builder_{ Response::getBuilder() };
    // Validate if the headers and the body are valid
    virtual void processRequestLine(const Request &) = 0;
    virtual void processHeaders(const Request &) = 0;
    virtual void processRequestBody(const std::string &body)
        = 0;
    virtual void constructResponseBody() = 0;
};

#endif // !HANDLER_HPP_
