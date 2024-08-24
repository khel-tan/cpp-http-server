#include "parser/IterativeParser.hpp"
#include "server/HttpServer.hpp"
#include "socket/TCPSocket.hpp"
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>

int parsePort(const char *arg, const int DEFAULT);

int main(int argc, char **argv) {
  std::cout << "Hello world" << std::endl;
  const int DEFAULT_PORT = 5100;
  const int PORT = argc > 1 ? parsePort(argv[1], DEFAULT_PORT) : DEFAULT_PORT;

  HttpServer server(std::make_unique<TCPSocket>(PORT),
                    std::make_unique<IterativeParser>());
  server.run();
}

int parsePort(const char *arg, const int DEFAULT) {
  try {
    return std::stoi(arg);
  } catch (std::invalid_argument) {
    return DEFAULT;
  }
}
