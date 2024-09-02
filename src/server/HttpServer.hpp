#ifndef HTTP_SERVER_HPP_

#define HTTP_SERVER_HPP_

#include "../handlers/Handler.hpp"
#include "../message/URI.hpp"
#include "../parser/RequestParser.hpp"
#include "../socket/Socket.hpp"
#include "Server.hpp"

#include <memory>
#include <unordered_map>
#include <utility>

/**
 * @brief A server that provides HTTP request handling
 * services
 *
 * HTTP Server handles management of resources
 * required to transform an HTTP request string into a
 * request object, pass said object to some handlers and
 * obtain some response string, send back the above string
 * over the network, and do error handling for all of the
 * above.
 *
 * Its dependencies are provided through Socket and
 * RequestParser interfaces.
 */
class HttpServer : public Server {
  public:
    HttpServer() = delete;
    /**
     * @brief Constructors HTTPServer from a pointer to a
     * socket and a parser
     *
     * Dependency injection is used to make the HttpServer
     * dependent only on the interface and not the
     * implementations. Unique pointers are used as it does
     * not make sense to share a network socket or a parser.
     *
     * @param sock unique pointer to a network socket
     * @param parser unique pointer to a http request parser
     */
    HttpServer(std::unique_ptr<Socket> &&sock,
               std::unique_ptr<RequestParser> &&parser)
        : socket_(std::move(sock)),
          parser_(std::move(parser))
    {
    }
    void run() override;
    /**
     * @brief Maps HTTP Request handlers from URI objects
     *
     *
     * @param uri The URI that we want to handle
     * @param handler The handler service
     */
    void
    mapHandler(const URI &uri,
               std::unique_ptr<Handler> &&handler)
    {
        // We move the pointers to ensure that only we own
        // the handling service
        requestHandlers_.insert_or_assign(
            uri, std::move(handler));
    }

  protected:
    const std::unique_ptr<Socket> socket_;
    const std::unique_ptr<RequestParser> parser_;
    std::unordered_map<URI, std::unique_ptr<Handler>,
                       URI::Hash, URI::Equality>
        requestHandlers_;

    /**
     * @brief Decide what to do with the request object we
     * got from the parser
     */
    void handleRequest(const Request &);
};

#endif // !HTTP_SERVER_HPP_
