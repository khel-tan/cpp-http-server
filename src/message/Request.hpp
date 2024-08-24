#ifndef REQUEST_HPP_

#define REQUEST_HPP_

#include "Message.hpp"
#include <string>
class RequestBuilder;
class Request : public Message {
public:
  friend class RequestBuilder;
  static RequestBuilder getBuilder();
  std::string toString() const;

protected:
  Request(){};
  Method method_;
};

class RequestBuilder {
public:
  RequestBuilder() : request_(Request()) {}
  void setHeaders(const Request::header_key key,
                  const Request::header_value value) {
    request_.headers_.insert_or_assign(key, value);
  }
  void setVersion(const Version version) { request_.version_ = version; }
  void setMethod(const Method method) { request_.method_ = method; }
  // TODO: Validation logic
  void validate() const {}
  Request build() const {
    validate();
    return request_;
  }

protected:
  Request request_;
};

#endif // !DEBUG
