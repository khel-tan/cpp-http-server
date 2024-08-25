#ifndef RESPONSE_HPP_

#define RESPONSE_HPP_

#include "Message.hpp"
enum class StatusCode {
    OK = 200,
    NOT_FOUND = 404,
};

std::string toString(const StatusCode &);

class ResponseBuilder;
class Response : public Message {
  public:
    friend class ResponseBuilder;
    static ResponseBuilder getBuilder();
    std::string toString() const;

  protected:
    Response()
    {
    }
    StatusCode statusCode_;
};

class ResponseBuilder {
  public:
    ResponseBuilder() : response_(Response())
    {
    }
    ResponseBuilder &
    setHeaders(const Response::header_key key,
               const Response::header_value value)
    {
        response_.headers_.insert_or_assign(key, value);
        return *this;
    }
    ResponseBuilder &
    setVersion(const Version version)
    {
        response_.version_ = version;
        return *this;
    }
    ResponseBuilder &
    setStatusCode(const StatusCode statusCode)
    {
        response_.statusCode_ = statusCode;
        return *this;
    }
    void
    validate() const
    {
    }
    Response
    build() const
    {
        validate();
        return response_;
    }

  private:
    Response response_;
};
#endif // !RESPONSE_HPP_
