#include "IterativeParser.hpp"
#include <iostream>
#include <regex>
#include <stdexcept>

void
IterativeParser::feedInput(std::string input)
{
    input_ += input;
}

void
IterativeParser::parse()
{
    std::stringstream ss(input_);

    std::string requestLine;
    std::getline(ss, requestLine);
    processRequestLine(requestLine);

    std::string line;

    // INFO: Works only with "\r" at the moment for insomnia
    while (std::getline(ss, line) && line != "\r") {
        // TODO: Trim key and value of whitespaces
        std::size_t colonPos = line.find(':');
        std::string key = line.substr(0, colonPos);
        std::string value = line.substr(colonPos + 1);

        builder_.setHeaders(key, value);
    }
    std::string body{};
    while (std::getline(ss, line)) {
        body += line;
    }
    builder_.setBody(body);
}

Request
IterativeParser::getRequest() const
{
    return builder_.build();
}

void
IterativeParser::processRequestLine(
    const std::string &requestLine)
{
    std::smatch matches;
    if (std::regex_match(requestLine, matches,
                         REQUEST_LINE_PATTERN)) {
        const auto method = matches[1];
        const auto uri = matches[2];
        const auto version = matches[3];

        for (const auto &m : matches) {
            std::cout << "Match : " << m << std::endl;
        }
        builder_.setMethod(parseMethod(method));
        builder_.setURI(URI(uri));
        builder_.setVersion(parseVersion(version));
    }
    else {
        throw std::invalid_argument(
            "Request line is invalid");
    }
}
