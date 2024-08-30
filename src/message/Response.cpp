#include "Response.hpp"
#include "Message.hpp"

#include <format>
#include <iostream>
#include <stdexcept>
#include <string>

std::string
toString(const StatusCode &statusCode)
{
    switch (statusCode) {
    case StatusCode::OK:
        return "OK";
    case StatusCode::CREATED:
        return "CREATED";
    case StatusCode::BAD_REQUEST:
        return "BAD_REQUEST";
    case StatusCode::NOT_FOUND:
        return "NOT FOUND";
    default:
        throw std::invalid_argument(
            "Status Code not recognized");
    }
}

int
toInt(const StatusCode &statusCode)
{
    return static_cast<int>(statusCode);
}

ResponseBuilder
Response::getBuilder()
{
    return ResponseBuilder();
}

std::string
Response::toTransmittableString() const
{
    std::string messageHeaders{};
    for (const auto &h : headers_) {
        messageHeaders
            += h.first + ": " + h.second + LINE_BREAK;
    }

    // clang-format off
    auto result = std::format("{} {} {}", ::toString(version_),
                       ::toInt(statusCode_),
                       ::toString(statusCode_))
           + LINE_BREAK
           + messageHeaders + LINE_BREAK;
    // clang-format on
    if (!body_.empty()) {
        result += body_ + LINE_BREAK;
    }
    return result + LINE_BREAK;
}
