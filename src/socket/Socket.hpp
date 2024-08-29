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
    virtual void acceptConnection() = 0;
    virtual void closeConnection() = 0;
    virtual std::string receiveData() = 0;
    virtual void sendData(const std::string &data) = 0;
    virtual void closeSocket() = 0;
};
#endif // !SOCKET_HPP_
