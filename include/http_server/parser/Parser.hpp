#ifndef PARSER_HPP_

#define PARSER_HPP_

#include "../message/Message.hpp"
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
namespace HttpServer {
template <typename ParsedType> class Parser {
public:
  virtual ParsedType parse(const std::string &input) = 0;
};

class RequestParser : public Parser<HttpServer::Request> {
public:
  Request parse(const std::string &input) override {
    if (input == "") {
      throw std::invalid_argument("Input is empty!");
    }
    std::stringstream ss(input);
    std::string line;
    while (std::getline(ss, line, '\n')) {
      std::cout << "Parsing -> " << line << std::endl;
    }
  }

private:
};

}; // namespace HttpServer
#endif
