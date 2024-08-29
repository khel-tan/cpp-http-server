#include "HttpServer.hpp"
#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <string>
#include <sys/socket.h>
void
HttpServer::run()
{
    std::cout << "Server is accepting requests..."
              << std::endl;
    while (true) {
        socket_->acceptConnection();
        auto data = socket_->receiveData();
        std::string inputStr(data.begin(), data.end());

        if (inputStr.length() != 0) {
            parser_->feedInput(inputStr);
            parser_->parse();
            auto request = parser_->getRequest();
            handleRequest(request);
            socket_->closeConnection();
        }
    }
}

void
HttpServer::sanitizeString(std::string &str)
{
    str.erase(std::remove_if(str.begin(), str.end(),
                             [](const char c) {
                                 return c == '\r'
                                        || c == '\n';
                             }),
              str.cend());
}

void
HttpServer::handleRequest(const Request &request)
{
    if (requestHandlers_.contains(request.getURI())) {
        auto response = requestHandlers_[request.getURI()]
                            ->handleRequest(request);
        socket_->sendData(response.toTransmittableString());
    }
    else {
        throw std::invalid_argument(
            "Cannot find any handlers for URI");
    }
}
