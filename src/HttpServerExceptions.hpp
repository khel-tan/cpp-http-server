#ifndef HTTP_SERVER_EXCEPTIONS_HPP_

#define HTTP_SERVER_EXCEPTIONS_HPP_
#include <exception>
#include <locale>
#include <string>
#include <system_error>

class InvalidMessage : public std::exception {
  protected:
    std::string message_;

  public:
    InvalidMessage(const std::string &message)
        : message_(message)
    {
    }

    const char *
    what() const noexcept override
    {
        return message_.c_str();
    }
};

class InvalidRequest : public InvalidMessage {
  public:
    InvalidRequest(const std::string &message)
        : InvalidMessage(message)
    {
    }
};

class InvalidRequestBody : public InvalidRequest {
  public:
    InvalidRequestBody(const std::string &message)
        : InvalidRequest(message)
    {
    }
};

class InvalidResponse : public InvalidMessage {
  public:
    InvalidResponse(const std::string &message)
        : InvalidMessage(message)
    {
    }
};

#endif // !HTTP_SERVER_EXCEPTIONS_HPP_
