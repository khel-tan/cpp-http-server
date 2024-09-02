#ifndef SOCKET_HPP_
#define SOCKET_HPP_
#include <string>

/*
 * Generic socket that wraps around the low level C API so
 * that the rest of our code work with Modern CPP constructs
 */
class Socket {
  public:
    virtual ~Socket() = default;

    /**
     * @brief Accepts connection from the client attempt at
     * the port that we are listening at
     */
    virtual void acceptConnection() = 0;
    /**
     * @brief Closes the client connection and cleans up
     */
    virtual void closeConnection() = 0;
    /**
     * @brief Receives data in the buffer from the
     * server-client connection
     */
    virtual std::string receiveData() = 0;
    /**
     * @brief Sends data to the connected client
     */
    virtual void sendData(const std::string &data) = 0;

    /**
     * @brief Closes the client connection, shuts down the
     * server socket and cleans up
     */
    virtual void closeSocket() = 0;
};
#endif // !SOCKET_HPP_
