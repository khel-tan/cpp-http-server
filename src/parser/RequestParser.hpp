#ifndef PARSER_HPP_

#define PARSER_HPP_

#include "../message/Request.hpp"
/*
 *  Abstract interface for parsing text input into HTTP
 * Request objects
 */
class RequestParser {
  public:
    // Whether the input is intended to be fed at once or
    // iteratively depends on the implementation
    virtual void feedInput(std::string input) = 0;
    virtual void parse() = 0;
    virtual Request getRequest() const = 0;
    // In case we want to reset the parser input and its
    // state
    virtual void clear() = 0;

  protected:
    Version
    parseVersion(const std::string input)
    {
        return toVersion(input);
    }
    Method
    parseMethod(const std::string input)
    {
        return toMethod(input);
    }
};
#endif
