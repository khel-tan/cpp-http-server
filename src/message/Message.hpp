#ifndef MESSAGE_HPP_

#define MESSAGE_HPP_

/*
 * INFO: Abstract class to consolidate data and operations
 * common to both http requests and responses
 */
#include <string>
#include <unordered_map>

/**
 * @brief Denotes HTTP version
 */
enum class Version {
    UNDEFINED,
    HTTP_1_0,
    HTTP_1_1,
};

/**
 * @brief Denotes all HTTP methods available in our app
 */
enum class Method {
    UNDEFINED,
    GET,
    POST,
    PUT,
    PATCH,
    DELETE,
};

/**
 * @brief converts an HTTP version enum to its string
 * equivalent
 */
std::string toString(const Version &);
/**
 * @brief  converts an HTTP method enum to its string
 * equivalent
 */
std::string toString(const Method &);

/**
 * @brief Tries to convert a string to an HTTP version enum
 */
Version toVersion(const std::string &);
/**
 * @brief Tries to convert a string to an HTTP method enum
 */
Method toMethod(const std::string &);

/**
 * @brief Abstract base class for grouping together common
 * properties and behaviours between HTTP requests and
 * responses
 */
class Message {
  public:
    using header_key = std::string;
    using header_value = std::string;
    using Headers
        = std::unordered_map<header_key, header_value>;
    virtual ~Message() = default;

    /**
     * @brief This method transforms an HTTP message to a
     * string that can be trasmitted over the network.
     *
     * @return a string transmittable over the network
     */
    virtual std::string toTransmittableString() const = 0;

  protected:
    // HTTP messages use \r\n for indicating a newline
    constexpr static std::string LINE_BREAK{ "\r\n" };
    Version version_;
    Headers headers_;
    std::string body_;
    /**
     * @brief This method sets HTTP headers.
     *
     * @param key header name
     * @param value value of the header
     */
    void
    setHeaders(const header_key &key,
               const header_value &value)
    {
        headers_.insert_or_assign(key, value);
    }
};

#endif // !MESSAGE_HPP_
