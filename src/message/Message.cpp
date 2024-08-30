#include "Message.hpp"
#include <format>
#include <stdexcept>

std::string
toString(const Version &version)
{
    switch (version) {
    case Version::HTTP_1_0:
        return "HTTP/1.0";
    case Version::HTTP_1_1:
        return "HTTP/1.1";
    default:
        throw std::invalid_argument(
            "Conversion from HTTP version to string "
            "failed. Unknown version!");
    }
}
std::string
toString(const Method &method)
{
    switch (method) {
    case Method::GET:
        return "GET";
    case Method::POST:
        return "POST";
    case Method::PUT:
        return "PUT";
    case Method::PATCH:
        return "PATCH";
    case Method::DELETE:
        return "DELETE";
    default:
        throw std::invalid_argument(
            "Conversion from HTTP method to string failed. "
            "Unknown method!");
    }
}

Version
toVersion(const std::string &input)
{
    if (input == "HTTP/1.0") {
        return Version::HTTP_1_0;
    }
    else if (input == "HTTP/1.1") {
        return Version::HTTP_1_1;
    }
    else {
        throw std::invalid_argument(std::format(
            "{0} is not a valid Http version string!",
            input));
    }
}

Method
toMethod(const std::string &input)
{
    if (input == "GET") {
        return Method::GET;
    }
    else if (input == "POST") {
        return Method::POST;
    }
    else if (input == "PUT") {
        return Method::PUT;
    }
    else if (input == "PATCH") {
        return Method::PATCH;
    }
    else if (input == "DELETE") {
        return Method::DELETE;
    }
    else {
        throw std::invalid_argument(std::format(
            "{0} is not a valid Http method string!",
            input));
    }
}
