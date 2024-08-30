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
Request::toTransmittableString() const
{
    std::string messageHeaders{};
    for (const auto &h : headers_) {
        messageHeaders
            += h.first + ": " + h.second + LINE_BREAK;
    }
    auto result
        = std::format("{} {} {}", ::toString(method_),
                      uri_.toString(), ::toString(version_))
          + LINE_BREAK + messageHeaders + LINE_BREAK;
    if (!body_.empty()) {
        result += body_ + LINE_BREAK;
    }
    return result + LINE_BREAK;
}
