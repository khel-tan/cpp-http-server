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
    
    //Accept connection from client
    virtual void acceptConnection() = 0;
    //Close connection with current client
    virtual void closeConnection() = 0;
    virtual std::string receiveData() = 0;
    virtual void sendData(const std::string &data) = 0;

    //Shut down server soket and clean up
    virtual void closeSocket() = 0;
};
#endif // !SOCKET_HPP_
