#ifndef PARSER_HPP_

#define PARSER_HPP_

#include "../message/Request.hpp"
/**
 * @brief Abstract interface for parsing text input into
 * HTTP Request objects
 */
class RequestParser {
  public:
    /**
     * @brief Feeds an input string to the parser.
     *
     * Whether the input is intended to be fed at once or
     * iteratively depends on the implementation
     *
     * @param input the input string
     */
    virtual void feedInput(std::string input) = 0;
    /**
     * @brief Starts parsing from the input all relevant
     * HTTP request info
     */
    virtual void parse() = 0;
    /**
     * @brief Get a request object after parsing.
     *
     * If we call this without parsing, RequestBuilder will
     * raise an error in its validation as not all mandatory
     * fields are fileld yet!
     */
    virtual Request getRequest() const = 0;
    /**
     * @brief Reset parser state and clear the input state
     */
    virtual void clear() = 0;
};
#endif
