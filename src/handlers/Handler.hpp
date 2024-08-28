#ifndef HANDLER_HPP_

#define HANDLER_HPP_

#include "../message/Request.hpp"
#include "../message/Response.hpp"
class Handler {
  public:
    virtual Response handleRequest(const Request &) = 0;

  protected:
    ResponseBuilder builder_{ Response::getBuilder() };
    // Validate if the headers and the body are valid
    virtual void validateRequest(const Request &) = 0;
    virtual void validateBody(const std::string &body) = 0;
};

#endif // !HANDLER_HPP_
