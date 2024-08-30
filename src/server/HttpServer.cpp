#include "HttpServer.hpp"
#include <algorithm>
#include <exception>
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
        try {
            socket_->acceptConnection();
            auto data = socket_->receiveData();
            std::string inputStr(data.begin(), data.end());

            if (inputStr.length() != 0) {
                parser_->feedInput(inputStr);
                parser_->parse();
                auto request = parser_->getRequest();
                handleRequest(request);
                parser_->clear();
                socket_->closeConnection();
            }
        }
        catch (const std::exception &e) {
            std::cerr << e.what() << std::endl;
        }
    }
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
