#ifndef HANDLER_HPP_

#define HANDLER_HPP_

#include "../message/Request.hpp"
#include "../message/Response.hpp"
class Handler {
  public:
    virtual Response handleRequest(const Request &) = 0;

  protected:
    virtual void validateRequest(const Request &) = 0;
};

#endif // !HANDLER_HPP_
