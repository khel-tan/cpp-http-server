#ifndef MESSAGE_HPP
#define MESSAGE_HPP
#include <map>
#include <stdexcept>
#include <string>
namespace http_server {
enum class HttpVersion {
  HTTP_1_1,
};
enum class HttpMethod {
  GET,
  POST,
  PUT,
  DELETE,
};

// Abstract class at the root of the message hierarchy
class HttpMessage {
  // TODO: This class could benefit from a builder
public:
  virtual ~HttpMessage() = default;

  // getters
  std::string getBody() const { return body_; }
  std::string getHeader(const std::string &header) const {
    throw std::logic_error("Not implemented");
  }

protected:
  HttpVersion version_;
  std::string body_;
  std::map<std::string, std::string> headers_;
};

class HttpRequest : public HttpMessage {
public:
  ~HttpRequest() = default;
};
} // namespace http_server
#endif // !MESSAGE_HPP
