#include "HttpServer.hpp"
#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <string>
void
HttpServer::run()
{
    socket_->acceptConnection();
    std::cout << "Server is accepting requests..."
              << std::endl;
    while (true) {
        std::cout << "Before" << std::endl;
        auto data = socket_->receiveData();
        std::cout << "After" << std::endl;
        std::string inputStr(data.begin(), data.end());
        std::cout << "Data : " << inputStr << std::endl;
        // TODO: Properly sanitize the input
        //        if (inputStr.length() == 0) {
        //            break;
        //        }
        //
        //        if (inputStr == "exit\r\n") {
        //            break;
        //        }
        if (inputStr.length() != 0) {
            parser_->feedInput(inputStr);
            parser_->parse();
            auto request = parser_->getRequest();
            std::cout << request.toString() << std::endl;
            handleRequest(request);
            return;
        }
        // auto request = parser_->getRequest();
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
        socket_->sendData(response.toString() + LINE_BREAK);
    }
    else {
        throw std::invalid_argument(
            "Cannot find any handlers for URI");
    }
}
