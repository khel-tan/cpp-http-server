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

/*
 * TODO: Write responsibilities for this class
 */
class HttpServer : public Server {
  public:
    HttpServer() = delete; // Dependency injection is the
                           // only legal construction
    HttpServer(std::unique_ptr<Socket> &&sock,
               std::unique_ptr<RequestParser> &&parser)
        : socket_(std::move(sock)),
          parser_(std::move(parser))
    {
    }
    void run() override;
    void
    mapHandler(const URI &u, std::unique_ptr<Handler> &&h)
    {
        requestHandlers_.insert_or_assign(u, std::move(h));
    }

  protected:
    const std::unique_ptr<Socket> socket_;
    const std::unique_ptr<RequestParser> parser_;
    std::unordered_map<URI, std::unique_ptr<Handler>,
                       URI::Hash, URI::Equality>
        requestHandlers_;
    void sanitizeString(std::string &str);
    void handleRequest(const Request &);
};

#endif // !HTTP_SERVER_HPP_
