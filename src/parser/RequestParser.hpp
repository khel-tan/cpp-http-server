#ifndef PARSER_HPP_

#define PARSER_HPP_

#include "../message/Request.hpp"
#include <regex>
class RequestParser {
public:
  virtual void feedInput(std::string input) = 0;
  virtual void parse() = 0;
  virtual Request getRequest() const = 0;

protected:
  Version parseVersion(const std::string &input) { return Version::HTTP_1_0; }
  Method parseMethod(const std::string &input) { return Method::GET; }
};
#endif
