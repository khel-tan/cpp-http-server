#ifndef ITERATIVE_PARSER_HPP_

#define ITERATIVE_PARSER_HPP_

#include "../message/Request.hpp"
#include "RequestParser.hpp"
#include <iostream>
#include <regex>
#include <sstream>
#include <stdexcept>
#include <string>
class IterativeParser : public RequestParser {
public:
  IterativeParser() : builder_(RequestBuilder()) {}
  void parse() override;
  void feedInput(std::string input) override;
  Request getRequest() const override;

protected:
  const std::regex REQUEST_LINE_PATTERN{R"((\w+)\s*(\W+)\s*)"};
  std::string input_{};
  RequestBuilder builder_;

  void processRequestLine(const std::string &);
};

#endif // !ITERATIVE_PARSER_HPP_
