#ifndef RESPONSE_HPP_

#define RESPONSE_HPP_

#include "../HttpServerExceptions.hpp"
#include "Message.hpp"
#include <iostream>
#include <stdexcept>
enum class StatusCode {
    UNDEFINED,
    OK = 200,
    CREATED = 201,
    BAD_REQUEST = 400,
    NOT_FOUND = 404,
};

std::string toString(const StatusCode &);
int toInt(const StatusCode &);

class ResponseBuilder;

/*
 * INFO: Represents all HTTP responses
 * The constructor is private and it is meant to be build
 * through its builder interface.
 */
class Response : public Message {
  public:
    friend class ResponseBuilder;
    static ResponseBuilder getBuilder();
    std::string toString() const;
    virtual std::string
    toTransmittableString() const override;

  protected:
    Response() {}
    StatusCode statusCode_;
};

/*
 * INFO: Builder to simplify the construction.
 * Before build, validation logic is performed to ensure
 * that we have a valid response
 */
class ResponseBuilder {
  public:
    ResponseBuilder() : response_(Response()) {}
    ResponseBuilder &
    setHeaders(const Response::header_key key,
               const Response::header_value value)
    {
        response_.setHeaders(key, value);
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
    ResponseBuilder &
    setBody(const std::string body)
    {
        response_.body_ = body;
        return *this;
    }
    void
    validate() const
    {
        if (response_.statusCode_ == StatusCode::UNDEFINED
            || response_.version_ == Version::UNDEFINED) {
            throw InvalidResponse(
                "Invalid HTTP Response construction. Some "
                "mandatory fields are missing");
        }
    }
    Response
    build() const
    {
        validate();
        return response_;
    }
    ResponseBuilder &
    reset()
    {
        response_ = Response();

        return *this;
    }

  private:
    Response response_;
};
#endif // !RESPONSE_HPP_
