#include "Message.hpp"
std::string toString(const Version &version) {
  switch (version) {
  case Version::HTTP_1_0:
    return "HTTP/1.0";
  case Version::HTTP_1_1:
    return "HTTP/1.1";
  default:
    throw std::invalid_argument("Http version not recognized!");
  }
}
std::string toString(const Method &method) {
  switch (method) {
  case Method::GET:
    return "GET";
  case Method::POST:
    return "POST";
  case Method::PUT:
    return "PUT";
  case Method::DELETE:
    return "DELETE";
  default:
    throw std::invalid_argument("Http method not recognized!");
  }
}
