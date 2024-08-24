#include "Request.hpp"
#include <format>
#include <string>

RequestBuilder Request::getBuilder() { return RequestBuilder(); }

std::string Request::toString() const {
  return "Request Object\n" +
         std::format("{0} / {1}", ::toString(method_), ::toString(version_));
}
