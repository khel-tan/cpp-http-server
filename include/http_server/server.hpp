#ifndef SERVER_HPP
#define SERVER_HPP

#include "Socket.hpp"
#include <memory>

// Abstract Server class
class Server {
protected:
  std::unique_ptr<Socket> socket_; // Unique pointer to manage Socket

public:
  virtual void run() = 0; // Pure virtual function for running the server

  // Virtual destructor for proper cleanup in derived classes
  virtual ~Server() = default;
};

// Concrete HttpServer class
class HttpServer : public Server {
public:
  // Constructor accepts a unique_ptr to a Socket object
  HttpServer(std::unique_ptr<Socket> &&sock) {
    this->socket_ = std::move(sock);
  }

  void run() override;
};

#endif // SERVER_HPP
