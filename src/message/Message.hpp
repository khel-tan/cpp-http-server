#ifndef MESSAGE_HPP_

#define MESSAGE_HPP_

/*
 * INFO: Abstract class to consolidate data and operations
 * common to both http requests and responses
 */
#include <iostream>
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

std::string toString(const Version &);
std::string toString(const Method &);

Version toVersion(const std::string &);
Method toMethod(const std::string &);

class Message {
  public:
    using header_key = std::string;
    using header_value = std::string;
    using Headers
        = std::unordered_map<header_key, header_value>;
    virtual ~Message() = default;
    virtual std::string toTransmittableString() const = 0;

  protected:
    Version version_;
    Headers headers_;
    std::string body_;
    void
    setHeaders(const header_key &key,
               const header_value &value)
    {
        headers_.insert_or_assign(key, value);
    }
};

#endif // !MESSAGE_HPP_
