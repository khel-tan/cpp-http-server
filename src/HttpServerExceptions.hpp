#ifndef HTTP_SERVER_EXCEPTIONS_HPP_

#define HTTP_SERVER_EXCEPTIONS_HPP_
#include <stdexcept>
#include <string>

class invalid_message : public std::runtime_error {

  public:
    invalid_message(const std::string &message)
        : std::runtime_error(message)
    {
    }
};

class invalid_request : public invalid_message {
  public:
    invalid_request(const std::string &message)
        : invalid_message(message)
    {
    }
};

// The body of the request is invalid
class invalid_request_body : public invalid_request {
  public:
    invalid_request_body(const std::string &message)
        : invalid_request(message)
    {
    }
};

// Whatever response object we have on hand is invalid
class invalid_response : public invalid_message {
  public:
    invalid_response(const std::string &message)
        : invalid_message(message)
    {
    }
};

class database_error : public std::runtime_error {
  public:
    database_error(const std::string &message)
        : std::runtime_error(message)
    {
    }
};

#endif // !HTTP_SERVER_EXCEPTIONS_HPP_
