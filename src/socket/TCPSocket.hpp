#ifndef TCP_SOCKET_HPP_

#define TCP_SOCKET_HPP_

#include "Socket.hpp"
#include <cstdint>
#include <string>
/**
 * @brief Sends and receives data over the network in TCP
 * streams
 */
class TCPSocket : public Socket {
  public:
    TCPSocket() = delete;
    explicit TCPSocket(std::uint16_t port);
    ~TCPSocket();
    TCPSocket(const TCPSocket &other) = delete;
    TCPSocket &operator=(const TCPSocket &) = delete;
    TCPSocket(TCPSocket &&);
    TCPSocket &operator=(TCPSocket &&other);
    void acceptConnection() override;
    void closeConnection() override;
    std::string receiveData() override;
    void sendData(const std::string &data) override;
    void closeSocket() override;

  protected:
    const std::size_t BUFFER_SIZE = 1024;
    int serverSocket_ = -1;
    int clientSocket_ = -1;
    void initialize();
};

#endif // !TCP_SOCKET_HPP_
