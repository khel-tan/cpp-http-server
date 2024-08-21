#include "../../include/http_server/server.hpp"
#include <iostream>

void HttpServer::run() {
  socket_->acceptConnection();
  while (true) {
    auto data = socket_->receiveData();
    if (data.size() == 0) {
      break;
    }
    std::cout << "Message : " << std::string(data.begin(), data.end())
              << std::endl;
  }
  socket_->closeSocket();
}
