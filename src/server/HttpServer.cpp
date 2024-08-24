#include "HttpServer.hpp"
#include <format>
#include <iostream>
#include <string>
void HttpServer::run() {
  socket_->acceptConnection();
  std::cout << "Server is accepting requests..." << std::endl;
  while (true) {
    auto data = socket_->receiveData();
    std::string inputStr(data.begin(), data.end());
    // TODO: Properly sanitize the input

    if (inputStr == "exit\r\n") {
      break;
    }
    parser_->feedInput(inputStr);
    auto request = parser_->getRequest();
  }
}

void HttpServer::sanitizeString(std::string &str) {
  str.erase(std::remove_if(str.begin(), str.end(),
                           [](const char c) { return c == '\r' || c == '\n'; }),
            str.cend());
}
