#ifndef MESSAGE_HPP
#define MESSAGE_HPP
#include <format>
#include <string>
#include <unordered_map>
enum class HttpVersion {
  HTTP_1_1,
};
enum class HttpMethod {
  GET,
  POST,
  PUT,
  DELETE,
};

std::string toString(const HttpVersion &version);
std::string toString(const HttpMethod &method);

class HttpMessage {
public:
  using header_key = std::string;
  using header_value = std::string;
  using Headers = std::unordered_map<header_key, header_value>;
  HttpMessage(Headers headers, HttpVersion version)
      : headers_(headers), version_(version) {}
  virtual ~HttpMessage() = default;
  HttpVersion getVersion() { return version_; }
  header_value getHeader(const header_key &key) {
    if (headers_.contains(key)) {
      return headers_.at(key);
    }

    // TODO: Maybe throw an error?
    return header_value{};
  }

  virtual std::string toString() = 0;

protected:
  const HttpVersion version_;
  const Headers headers_;
};

class HttpRequest : public HttpMessage {
public:
  HttpRequest(HttpMethod method, Headers headers,
              HttpVersion version = HttpVersion::HTTP_1_1)
      : method_(method), HttpMessage(headers, version) {}
  std::string toString() override {
    return std::format("{0} / {1}", ::toString(method_), ::toString(version_));
  }

protected:
  const HttpMethod method_;
};

#endif // !MESSAGE_HPP
