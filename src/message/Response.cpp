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
    case StatusCode::BAD_REQUEST:
        return "BAD_REQUEST";
    case StatusCode::NOT_FOUND:
        return "NOT FOUND";
    default:
        throw std::invalid_argument(
            "Statuscode not recognized");
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
Response::toString() const
{
    return std::format("{0} {1} {2}", ::toString(version_),
                       ::toInt(statusCode_),
                       ::toString(statusCode_));
}
