#ifndef REQUEST_HPP_

#define REQUEST_HPP_

#include "Message.hpp"
#include "URI.hpp"
#include <string>
class RequestBuilder;
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

  protected:
    Request(){};
    Method method_;
    URI uri_;
};

class RequestBuilder {
  public:
    RequestBuilder() : request_(Request())
    {
    }
    RequestBuilder &
    setHeaders(const Request::header_key key,
               const Request::header_value value)
    {
        request_.headers_.insert_or_assign(key, value);
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
    // TODO: Validation logic
    void
    validate() const
    {
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
