#include "TCPSocket.hpp"
#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <netinet/in.h>
#include <stdexcept>
#include <sys/socket.h>
#include <unistd.h>
#include <vector>

// TODO: Initialization should be encapsulated
TCPSocket::TCPSocket(std::uint16_t port)
    : serverSocket_(socket(AF_INET, SOCK_STREAM, 0))
{
    if (serverSocket_ == -1) {
        throw std::runtime_error(
            "TCP socket creation failed");
    }
    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(port);

    if (bind(serverSocket_,
             (struct sockaddr *)&serverAddress,
             sizeof(serverAddress))
        == -1) {
        closeSocket();
        throw std::runtime_error(
            "Error binding the socket!");
    }
    if (listen(serverSocket_, 1) == -1) {
        closeSocket();
        throw std::runtime_error(
            "Error listening on the socket!");
    }
}

TCPSocket::~TCPSocket()
{
    // BUG: Socket does not close properly
    //  The binding is not released when the socket is
    //  destructed
    closeSocket();
}

TCPSocket::TCPSocket(TCPSocket &&other)
    : serverSocket_(other.serverSocket_),
      clientSocket_(other.clientSocket_)
{
    other.serverSocket_ = -1;
    other.clientSocket_ = -1;
}
void
TCPSocket::acceptConnection()
{
    clientSocket_ = accept(serverSocket_, NULL, NULL);
    if (clientSocket_ == -1) {
        throw std::runtime_error(
            "Error accepting client connection!");
    }
}

void
TCPSocket::closeConnection()
{
    if (clientSocket_ != -1) {
        close(clientSocket_);
    }
}

std::string
TCPSocket::receiveData()
{
    // NOTE: Stop trimming the buffer of \n and \r.
    //  The socket is not responsible for that.
    std::vector<char> buffer(BUFFER_SIZE);
    int bytesReceived = recv(clientSocket_, buffer.data(),
                             buffer.size(), 0);
    if (bytesReceived <= 0) {
        return std::string();
    }
    buffer.resize(bytesReceived);
    return std::string(buffer.begin(), buffer.end());
}

void
TCPSocket::sendData(const std::string &data)
{
    if (clientSocket_ == -1) {
        throw std::runtime_error(
            "No client connected to send the data!");
    }

    std::size_t bytesSent
        = send(clientSocket_, data.c_str(), data.size(), 0);
    if (bytesSent == -1) {
        throw std::runtime_error(
            "Error sending data to client!");
    }
}

void
TCPSocket::closeSocket()
{
    if (serverSocket_ != -1) {
        close(serverSocket_);
    }
    if (clientSocket_ != -1) {
        close(clientSocket_);
    }
}
