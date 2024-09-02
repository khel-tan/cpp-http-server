#ifndef HANDLER_HPP_

#define HANDLER_HPP_

#include "../HttpServerExceptions.hpp"
#include "../message/Request.hpp"
#include "../message/Response.hpp"
#include <iostream>

/**
 * @brief Abstract class for handling HTTP requests and
 * outputting a Response object
 */
class Handler {
  public:
    /**
     * @brief Processes an HTTP Request object and returns a
     * Response object.
     *
     * This method handles the entire request processing
     * including request lines, headers and response
     * construction. It also handles exceptions thrown and
     * outputs an appropriate response.
     *
     * @param request The HTTP request to process.
     * @return A Response object based on the processed
     * request.
     */
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
    /**
     * @brief The instance's own Response builder instance
     */
    ResponseBuilder builder_{ Response::getBuilder() };
    // The following 4 methods plus maybe some extra ones
    // are called in handleRequest. Each method
    // incrementally gives more info to builder_
    /**
     * @brief Processes the request line and checks if the
     * method and the HTTP version and the URI are
     * appropriate
     *
     * @param request request to process
     */
    virtual void processRequestLine(const Request &request)
        = 0;
    /**
     * @brief Processes headers of the request
     *
     * @param request request to process
     */
    virtual void processHeaders(const Request &request) = 0;
    /**
     * @brief Processes the body of the request
     *
     * This is more relevant for requests that intend to
     * create or modify server-side resources.
     *
     * @param body the body of the HTTP request
     */
    virtual void processRequestBody(const std::string &body)
        = 0;
    /**
     * @brief Constructs Response Body if appropriate
     *
     * Contrary to processHeaders(), this method will be
     * empty for handlers that concern letting clients view
     * resources in readonly mode
     */
    virtual void constructResponseBody() = 0;
};

#endif // !HANDLER_HPP_
