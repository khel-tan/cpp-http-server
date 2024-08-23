#include "../../../include/http_server/server/HttpServer.hpp"
#include <iostream>

namespace HttpServer {

void HttpServer::run() {
  socket_->acceptConnection();
  while (true) {
    auto data = socket_->receiveData();
    auto inputStr = std::string(data.begin(), data.end());
    if (data.size() == 0) {
      break;
    }
    std::cout << inputStr << std::endl;
  }
  socket_->closeSocket();
}
} // namespace HttpServer
