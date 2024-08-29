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
    return "Request Object\n"
           + std::format("{0} {1} {2}", ::toString(method_),
                         uri_.toString(),
                         ::toString(version_));
}

std::string
Request::toTransmittableString() const
{
    std::string messageHeaders{};
    for (const auto &h : headers_) {
        messageHeaders
            += h.first + ": " + h.second + "\r\n";
    }
    return std::format("{} {} {}", ::toString(method_),
                       uri_.toString(),
                       ::toString(version_))
           + "\r\n" + messageHeaders + "\r\n" + body_
           + "\r\n" + "\r\n";
}
