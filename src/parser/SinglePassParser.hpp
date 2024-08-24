#ifndef SINGLE_PASS_PARSER_HPP_

#define SINGLE_PASS_PARSER_HPP_

#include "../message/Request.hpp"
#include "RequestParser.hpp"
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
class SinglePassParser : public RequestParser {
public:
  SinglePassParser() : builder_(RequestBuilder()) {}
  void feedInput(std::string input) override { input_ = input; }
  Request getRequest() const override {
    std::stringstream ss(input_);
    std::string line;
    while (std::getline(ss, line)) {
      std::cout << line << std::endl;
    }

    throw std::logic_error("Unimplemented");
  }

protected:
  std::string input_;
  RequestBuilder builder_;
};

#endif // !SINGLE_PASS_PARSER_HPP_
