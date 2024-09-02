#ifndef REQUEST_HPP_

#define REQUEST_HPP_

#include "../HttpServerExceptions.hpp"
#include "Message.hpp"
#include "URI.hpp"
#include <string>
class RequestBuilder;

/**
 * @brief This class represents all HTTP requests.
 * It can be built only through its builder interface!
 */
class Request : public Message {
  public:
    friend class RequestBuilder;
    /**
     * @brief The only starting point for building a Request
     * object
     *
     */
    static RequestBuilder getBuilder();
    /**
     * @brief constant getter for URI
     */
    const URI &
    getURI() const
    {
        return uri_;
    }
    /**
     * @brief constant getter for method
     */
    Method
    getMethod() const
    {
        return method_;
    }
    /**
     * @brief constant getter for request body
     */
    std::string
    getBody() const
    {
        return body_;
    }
    /**
     * @brief constant getter for version
     */
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

/**
 * @brief Simplifies construction logic of Request.
 * When build() is called, it also performs validation of
 * the request
 */
class RequestBuilder {
  public:
    RequestBuilder() : request_(Request()) {}
    RequestBuilder &
    setHeaders(const Request::header_key &key,
               const Request::header_value &value)
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
    /**
     * @brief Ensures that our request object has all
     * mandatory fields
     */
    void
    validate() const
    {
        if (request_.uri_.toString().empty()) {
            throw invalid_request("Request validation "
                                  "failed: URI is missing");
        }
        if (request_.getMethod() == Method::UNDEFINED) {
            throw invalid_request(
                "Request validation failed: Method is "
                "missing");
        }
        if (request_.getVersion() == Version::UNDEFINED) {
            throw invalid_request(
                "Request validation failed: Version is "
                "missing");
        }
    }
    /**
     * @brief Validate and build the request as far as we
     * have constructed
     */
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
