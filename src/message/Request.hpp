#ifndef REQUEST_HPP_

#define REQUEST_HPP_

#include "../HttpServerExceptions.hpp"
#include "Message.hpp"
#include "URI.hpp"
#include <stdexcept>
#include <string>
class RequestBuilder;

/*
 * INFO: Represents all HTTP requests.
 * Can be built only through its builder interface!
 */
class Request : public Message {
  public:
    friend class RequestBuilder;
    static RequestBuilder getBuilder();
    std::string toString() const;
    const URI &
    getURI() const
    {
        return uri_;
    }
    Method
    getMethod() const
    {
        return method_;
    }
    std::string
    getBody() const
    {
        return body_;
    }
    Version
    getVersion() const
    {
        return version_;
    }

    std::string toTransmittableString() const override;

  protected:
    Request(){};
    Method method_ = Method::UNDEFINED;
    URI uri_ = URI("");
};

/*
 * INFO: Simplifies construction logic of Request.
 * When build() is called, it also performs validation of
 * the request
 */
class RequestBuilder {
  public:
    RequestBuilder() : request_(Request()) {}
    RequestBuilder &
    setHeaders(const Request::header_key key,
               const Request::header_value value)
    {
        request_.setHeaders(key, value);
        return *this;
    }
    RequestBuilder &
    setVersion(const Version version)
    {
        request_.version_ = version;
        return *this;
    }
    RequestBuilder &
    setMethod(const Method method)
    {
        request_.method_ = method;
        return *this;
    }
    RequestBuilder &
    setURI(const URI uri)
    {
        request_.uri_ = uri;
        return *this;
    }
    RequestBuilder &
    setBody(const std::string body)
    {
        request_.body_ = body;
        return *this;
    }
    // TODO: Validation logic
    void
    validate() const
    {
        if (request_.uri_.toString() == ""
            || request_.getMethod() == Method::UNDEFINED
            || request_.getVersion()
                   == Version::UNDEFINED) {
            throw InvalidRequest(
                "HTTP Request construction has some "
                "missing mandatory values");
        }
    }
    Request
    build() const
    {
        validate();
        return request_;
    }

  protected:
    Request request_;
};

#endif // !DEBUG
