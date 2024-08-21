#include "../include/http_server/TCPSocket.hpp"
#include "../include/http_server/server.hpp"
#include <cstdint>
#include <memory>

int main() {
  std::uint16_t port = 5021;
  auto socketPtr = std::make_unique<TCPSocket>(port);
  HttpServer server(std::move(socketPtr));
  server.run();
}
