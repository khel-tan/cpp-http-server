#ifndef MESSAGE_HPP_
#define MESSAGE_HPP_

#include <string>
#include <unordered_map>
namespace HttpServer {
using header_key = std::string;
using header_value = std::string;

enum class Version {
  HTTP_1_0,
  HTTP_1_1,
};

enum class Method {
  GET,
};

enum class StatusCode {
  NOT_FOUND = 404,
};
template <class Derived> class Message {
public:
  virtual ~Message() = default;
  virtual void validate() = 0;

  virtual Derived &setHeader(const header_key &key, header_value value) {
    headers_.insert_or_assign(key, value);
    return static_cast<Derived &>(*this);
  };

protected:
  std::unordered_map<header_key, header_value> headers_;
  Version version_;
};

class Request : public Message<Request> {
public:
  ~Request() = default;

  void validate() override;

protected:
  Method method_;
};

class Response : public Message<Response> {
public:
  ~Response() = default;

  void validate() override;

protected:
  StatusCode status_code_;
};
}; // namespace HttpServer
#endif
