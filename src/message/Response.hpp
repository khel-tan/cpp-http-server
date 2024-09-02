#ifndef RESPONSE_HPP_

#define RESPONSE_HPP_

#include "../HttpServerExceptions.hpp"
#include "Message.hpp"

/**
 * @brief Enum class representing HTTP status codes
 */
enum class StatusCode {
    UNDEFINED,
    OK = 200,
    CREATED = 201,
    BAD_REQUEST = 400,
    NOT_FOUND = 404,
    INTERNAL_SERVER_ERROR = 500,
};

/**
 * @brief Converts a StatusCode object to a string
 */
std::string toString(const StatusCode &);

/**
 * @brief Casts a StatusCode object to its corresponding
 * integer code
 */
int toInt(const StatusCode &);

class ResponseBuilder;

/**
 * @brief Represents all HTTP responses
 * The constructor is private and it is meant to be build
 * through its builder interface.
 */
class Response : public Message {
  public:
    friend class ResponseBuilder;
    /**
     * @brief Gets a ResponseBuilder instance
     *
     * This is the only entry point to constructing a
     * Response object
     */
    static ResponseBuilder getBuilder();
    virtual std::string
    toTransmittableString() const override;

  protected:
    Response() {}
    StatusCode statusCode_;
};

/**
 * @brief Builder to simplify the construction.
 * Before build, validation logic is performed to ensure
 * that we have a valid response
 */
class ResponseBuilder {
  public:
    ResponseBuilder() : response_(Response()) {}
    ResponseBuilder &
    setHeaders(const Response::header_key key,
               const Response::header_value value)
    {
        response_.setHeaders(key, value);
        return *this;
    }
    ResponseBuilder &
    setVersion(const Version version)
    {
        response_.version_ = version;
        return *this;
    }
    ResponseBuilder &
    setStatusCode(const StatusCode statusCode)
    {
        response_.statusCode_ = statusCode;
        return *this;
    }
    ResponseBuilder &
    setBody(const std::string body)
    {
        response_.body_ = body;
        return *this;
    }
    /**
     * @brief Validate the response until how it has been
     * built thus far and throws an error if mandatory
     * fields are missing
     */
    void
    validate() const
    {
        if (response_.statusCode_
            == StatusCode::UNDEFINED) {
            throw invalid_response(
                "HTTP Response validation failed: Status "
                "code is missing");
        }
        if (response_.version_ == Version::UNDEFINED) {
            throw invalid_response(
                "HTTP Response validation failed: Version "
                "is missing");
        }
    }
    /**
     * @brief validates the response and returns it if valid
     */
    Response
    build() const
    {
        validate();
        return response_;
    }
    /**
     * @brief Reset the construction process
     */
    ResponseBuilder &
    reset()
    {
        response_ = Response();

        return *this;
    }

  private:
    Response response_;
};
#endif // !RESPONSE_HPP_
