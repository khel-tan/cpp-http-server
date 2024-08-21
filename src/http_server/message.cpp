#include "../../include/http_server/message.hpp"
#include <stdexcept>

std::string toString(const HttpVersion &version) {
  switch (version) {
  case HttpVersion::HTTP_1_1:
    return "HTTP/1.1";
  default:
    throw std::logic_error("Http version not recognized");
  }
}

std::string toString(const HttpMethod &method) {
  switch (method) {
  case HttpMethod::GET:
    return "GET";
  case HttpMethod::PUT:
    return "PUT";
  case HttpMethod::POST:
    return "POST";
  case HttpMethod::DELETE:
    return "DELETE";
  default:
    throw std::logic_error("Http method not recognized");
  }
}
