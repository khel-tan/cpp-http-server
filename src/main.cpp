#include "../include/http_server/server/HttpServer.hpp"
#include "../include/http_server/socket/TCPSocket.hpp"
#include <memory>
int main() {
  auto socket = std::make_unique<HttpServer::TCPSocket>(5100);
  auto server = HttpServer::HttpServer(std::move(socket));
  server.run();
}
