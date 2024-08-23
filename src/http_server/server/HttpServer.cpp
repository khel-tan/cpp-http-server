#include "../../../include/http_server/server/HttpServer.hpp"
#include <iostream>

namespace HttpServer {

void HttpServer::run() {
  socket_->acceptConnection();
  while (true) {
    auto data = socket_->receiveData();
    if (data.size() == 0) {
      break;
    }
    std::cout << std::string(data.begin(), data.end()) << std::endl;
  }
  socket_->closeSocket();
}
} // namespace HttpServer
