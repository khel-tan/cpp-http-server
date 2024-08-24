#ifndef REQUEST_HPP_

#define REQUEST_HPP_

#include "Message.hpp"
class RequestBuilder;
class Request : public Message {
public:
  friend class RequestBuilder;
  static RequestBuilder getBuilder();

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
  void validate() {}
  Request build() {
    validate();
    return request_;
  }

protected:
  Request request_;
};

#endif // !DEBUG
