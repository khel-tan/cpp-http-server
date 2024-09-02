#ifndef HTTP_SERVER_EXCEPTIONS_HPP_

#define HTTP_SERVER_EXCEPTIONS_HPP_
#include <stdexcept>
#include <string>

/**
 * @brief Base class to denote invalid HTTP request messages
 */
class invalid_message : public std::runtime_error {

  public:
    invalid_message(const std::string &message)
        : std::runtime_error(message)
    {
    }
};

/**
 * @brief Denotes invalid HTTP requests
 */
class invalid_request : public invalid_message {
  public:
    invalid_request(const std::string &message)
        : invalid_message(message)
    {
    }
};

/**
 * @brief The request of the body is invalid. For instance,
 * not having a valid JSON when we expect JSON, etc.
 */
class invalid_request_body : public invalid_request {
  public:
    invalid_request_body(const std::string &message)
        : invalid_request(message)
    {
    }
};

/**
 * @brief Denotes an invalid response object
 */
class invalid_response : public invalid_message {
  public:
    invalid_response(const std::string &message)
        : invalid_message(message)
    {
    }
};

/**
 * @brief There was a problem while using the database.
 */
class database_error : public std::runtime_error {
  public:
    database_error(const std::string &message)
        : std::runtime_error(message)
    {
    }
};

#endif // !HTTP_SERVER_EXCEPTIONS_HPP_
