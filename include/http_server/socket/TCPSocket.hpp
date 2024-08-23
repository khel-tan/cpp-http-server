#ifndef TCP_SOCKET_HPP_
#define TCP_SOCKET_HPP_

#include "Socket.hpp"

#include <arpa/inet.h>
#include <cstdint>
#include <sys/socket.h>
#include <unistd.h>
#include <vector>

class TCPSocket : public Socket {
public:
  explicit TCPSocket(std::uint16_t port);
  ~TCPSocket();
  void acceptConnection() override;
  std::vector<char> receiveData() override;
  void closeSocket() override;

protected:
  const std::size_t BUFFER_SIZE = 1024;
  int serverSocket_ = -1;
  int clientSocket_ = -1;
  void initialize();
};
#endif // !TCP_SOCKET_HPP_
