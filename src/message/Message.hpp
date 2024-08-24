#ifndef MESSAGE_HPP_

#define MESSAGE_HPP_

/*
 * INFO: Abstract class to consolidate data and operations common
 * to both http requests and responses
 */
#include <string>
#include <unordered_map>

enum class Version {
  HTTP_1_0,
  HTTP_1_1,
};
enum class Method {
  GET,
  POST,
  PUT,
  DELETE,
};
class Message {
public:
  using header_key = std::string;
  using header_value = std::string;
  using Headers = std::unordered_map<header_key, header_value>;
  virtual ~Message() = default;

protected:
  Version version_;
  Headers headers_;
};

#endif // !MESSAGE_HPP_
