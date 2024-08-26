#include "Request.hpp"
#include "Message.hpp"
#include <format>
#include <iostream>
#include <string>

RequestBuilder
Request::getBuilder()
{
    return RequestBuilder();
}

std::string
Request::toString() const
{
    for (const auto &h : headers_) {
        std::cout << h.first << ":" << h.second
                  << std::endl;
    }
    std::cout << body_ << std::endl;
    return "Request Object\n"
           + std::format("{0} {1} {2}", ::toString(method_),
                         uri_.toString(),
                         ::toString(version_));
}
