#include "../include/Logger.hpp"
#include <string>
int main() {
  for (int i = 0; i < 15; i++) {
    Logger::getInstance().log(std::to_string((i)), LogLevel::DEBUG);
  }
}
