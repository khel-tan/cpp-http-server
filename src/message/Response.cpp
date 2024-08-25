#include "Response.hpp"
#include "Message.hpp"

#include <format>
#include <stdexcept>
#include <string>

std::string
toString(const StatusCode &statusCode)
{
    switch (statusCode) {
    case StatusCode::OK:
        return "OK";
    case StatusCode::NOT_FOUND:
        return "NOT FOUND";
    default:
        throw std::invalid_argument(
            "Statuscode not recognized");
    }
}

ResponseBuilder
Response::getBuilder()
{
    return ResponseBuilder();
}

std::string
Response::toString() const
{
    return std::format("{0} {1}", ::toString(version_),
                       ::toString(statusCode_));
}
