#include "IterativeParser.hpp"
#include <regex>
#include <stdexcept>

void IterativeParser::feedInput(std::string input) { input_ += input; }

void IterativeParser::parse() {
  std::stringstream ss(input_);

  std::string requestLine;
  std::getline(ss, requestLine);
  processRequestLine(requestLine);

  std::string line;
  while (std::getline(ss, line)) {
    std::cout << "Line " << std::endl;
    std::cout << line << std::endl;
  }
}

Request IterativeParser::getRequest() const { return builder_.build(); }

void IterativeParser::processRequestLine(const std::string &requestLine) {
  std::smatch matches;
  if (std::regex_match(requestLine, matches, REQUEST_LINE_PATTERN)) {
    const auto method = matches[0];
    const auto uri = matches[1];
    // TODO: Get rid of the magic constant below
    const auto version = "HTTP/1.0";

    builder_.setMethod(parseMethod(method));
    builder_.setVersion(parseVersion(version));
  } else {
    throw std::invalid_argument("Request line is invalid");
  }
}
