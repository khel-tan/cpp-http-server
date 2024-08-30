#include "IterativeParser.hpp"
#include "../HttpServerExceptions.hpp"
#include "../utils/Utils.hpp"
#include <iostream>
#include <regex>
#include <stdexcept>

void
IterativeParser::feedInput(std::string input)
{
    // IDEA: Is there a more efficient way?
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

    // WARN: stringstream removes \n but http linebreaks are
    // \r\n That is why we use \r for content separation

    while (std::getline(ss, line) && line != "\r") {
        std::size_t colonPos = line.find(':');
        std::string key = line.substr(0, colonPos);
        std::string value = line.substr(colonPos + 1);

        // Trim whitespace
        trim(key);
        trim(value);
        // NOTE: Malformed headers might indicate bigger
        // problems
        if (key == "" || value == "") {
            continue;
        }

        builder_.setHeaders(key, value);
    }
    std::string body{};
    while (std::getline(ss, line) && line != "\r") {
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
        // TODO: What about invalid URI values and edge
        // cases?
        const auto uri = matches[2];
        const auto version = matches[3];

        for (const auto &m : matches) {
        }
        builder_.setMethod(parseMethod(method));
        builder_.setURI(URI(uri));
        builder_.setVersion(parseVersion(version));
    }
    else {
        throw invalid_request("Request line is invalid");
    }
}
