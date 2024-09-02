#ifndef ITERATIVE_PARSER_HPP_

#define ITERATIVE_PARSER_HPP_

#include "../message/Request.hpp"
#include "RequestParser.hpp"
#include <regex>
#include <string>
/**
 * @brief Iterative parser can be fed the input
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
        // The builder must also be reset as it is stateful
        builder_ = Request::getBuilder();
    }

  protected:
    /*
     * Regex pattern specifying the structure of a
     * request line
     */
    const std::regex REQUEST_LINE_PATTERN{
        // NOTE: The \r\n at the end can throw off regex and
        // can be hard to debug
        // clang-format off
            R"((\w+)\s+([^\s]+)\s+(HTTP/(\d+(\.\d+)?))\s+)"
        // clang-format on
    };
    std::string input_{};
    RequestBuilder builder_;

    /**
     * @brief processes request line and gives information
     * to builder_
     */
    void processRequestLine(const std::string &);
};

#endif
