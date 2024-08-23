#ifndef MESSAGE_HPP_
#define MESSAGE_HPP_

#include <string>
#include <unordered_map>
namespace HttpServer {
using header_key = std::string;
using header_value = std::string;

enum class HttpVersion {
  HTTP_1_1,
};

enum class HttpMethod {
  GET,
};

template <class Derived> class Message {
public:
  virtual ~Message() = default;
  virtual void validate() = 0;

  virtual Derived &setHeader(const header_key &key, header_value value) {
    headers_.insert_or_assign(key, value);
    return *this;
  };

protected:
  std::unordered_map<header_key, header_value> headers_;
  HttpVersion version_;
};

class Request : public Message<Request> {
public:
  ~Request() = default;

  void validate() override;

protected:
  HttpMethod method_;
};
}; // namespace HttpServer
#endif
