#ifndef ITERATIVE_PARSER_HPP_

#define ITERATIVE_PARSER_HPP_

#include "../message/Request.hpp"
#include "RequestParser.hpp"
#include <regex>
#include <string>
/*
 * INFO: Iterative parser can be fed the input
 * many times instead of all at once.
 */
class IterativeParser : public RequestParser {
  public:
    IterativeParser() : builder_(RequestBuilder()) {}
    void parse() override;
    void feedInput(std::string input) override;
    Request getRequest() const override;
    void
    clear() override
    {
        input_ = "";
        builder_ = Request::getBuilder();
    }

  protected:
    const std::regex REQUEST_LINE_PATTERN{
        // NOTE: The \r\n at the end can throw off regex and
        // can be hard to debug
        // clang-format off
            R"((\w+)\s+([^\s]+)\s+(HTTP/(\d+(\.\d+)?))\s+)"
        // clang-format on
    };
    std::string input_{};
    RequestBuilder builder_;

    void processRequestLine(const std::string &);
};

#endif
