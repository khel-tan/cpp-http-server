#ifndef TCP_SOCKET_HPP_

#define TCP_SOCKET_HPP_

#include "Socket.hpp"
#include <cstdint>
#include <string>
class TCPSocket : public Socket {
public:
  TCPSocket() = delete;
  explicit TCPSocket(std::uint16_t port);
  ~TCPSocket();
  void acceptConnection() override;
  std::string receiveData() override;
  void closeSocket() override;

protected:
  const std::size_t BUFFER_SIZE = 1024;
  int serverSocket_ = -1;
  int clientSocket_ = -1;
  void initialize();
};

#endif // !TCP_SOCKET_HPP_
