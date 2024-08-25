#ifndef HTTP_SERVER_HPP_

#define HTTP_SERVER_HPP_

#include "../handlers/Handler.hpp"
#include "../message/URI.hpp"
#include "../parser/RequestParser.hpp"
#include "../socket/Socket.hpp"
#include "Server.hpp"

#include <memory>
#include <unordered_map>

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

  protected:
    const std::unique_ptr<Socket> socket_;
    const std::unique_ptr<RequestParser> parser_;
    const std::unordered_map<URI, Handler, URI::Hash>
        requestHandlers_;
    void sanitizeString(std::string &str);
};

#endif // !HTTP_SERVER_HPP_
