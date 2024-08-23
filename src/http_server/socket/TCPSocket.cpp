#include "../../../include/http_server/socket/TCPSocket.hpp"
#include <cstddef>
#include <cstdint>
#include <netinet/in.h>
#include <stdexcept>
#include <sys/socket.h>

TCPSocket::TCPSocket(std::uint16_t port)
    : serverSocket_(socket(AF_INET, SOCK_STREAM, 0)) {
  if (serverSocket_ == -1) {
    throw std::runtime_error("TCP socket creation failed");
  }
  sockaddr_in serverAddress;
  serverAddress.sin_family = AF_INET;
  serverAddress.sin_addr.s_addr = INADDR_ANY;
  serverAddress.sin_port = htons(port);

  if (bind(serverSocket_, (struct sockaddr *)&serverAddress,
           sizeof(serverAddress)) == -1) {
    closeSocket();
    throw std::runtime_error("Error binding the socket!");
  }
  if (listen(serverSocket_, 1) == -1) {
    closeSocket();
    throw std::runtime_error("Error listening on the socket!");
  }
}

TCPSocket::~TCPSocket() { closeSocket(); }
void TCPSocket::acceptConnection() {
  clientSocket_ = accept(serverSocket_, NULL, NULL);
  if (clientSocket_ == -1) {
    throw std::runtime_error("Error accepting client connection!");
  }
}

std::vector<char> TCPSocket::receiveData() {
  std::vector<char> buffer(BUFFER_SIZE);
  int bytesReceived = recv(clientSocket_, buffer.data(), buffer.size(), 0);
  if (bytesReceived <= 0) {
    buffer.clear();
  }
  return buffer;
}

void TCPSocket::closeSocket() {
  if (serverSocket_ != -1) {
    close(serverSocket_);
  }
  if (clientSocket_ != -1) {
    close(clientSocket_);
  }
}
