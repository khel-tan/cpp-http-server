#ifndef SERVER_HPP_

#define SERVER_HPP_

#include "../socket/Socket.hpp"
#include <iostream>
#include <memory>

namespace HttpServer {

class HttpServer {
public:
  HttpServer(std::unique_ptr<Socket> &&socket) : socket_(std::move(socket)) {}

  void run();

protected:
  std::unique_ptr<Socket> socket_;
};
} // namespace HttpServer
#endif // !SERVER_HPP_
