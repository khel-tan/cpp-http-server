#ifndef RESPONSE_HPP_

#define RESPONSE_HPP_

#include "Message.hpp"
enum class StatusCode {
    OK = 200,
    NOT_FOUND = 404,
};

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
    void
    setHeaders(const Response::header_key key,
               const Response::header_value value)
    {
        response_.headers_.insert_or_assign(key, value);
    }
    void
    setVersion(const Version version)
    {
        response_.version_ = version;
    }
    void
    setStatusCode(const StatusCode statusCode)
    {
        response_.statusCode_ = statusCode;
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
