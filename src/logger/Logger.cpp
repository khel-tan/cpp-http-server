#include "../../include/logger/Logger.hpp"
#include <iostream>
#include <stdexcept>
namespace logger {
Logger &Logger::getInstance() {
  static Logger INSTANCE;
  return INSTANCE;
}

void Logger::log(const std::string &message, LogLevel level = LogLevel::INFO) {
  // TODO: Different logging for different levels
  std::cout << message << std::endl;
}
void Logger::setOutput(OutputType output) {
  throw std::logic_error("Not implemented");
}

Logger::Logger() {}
} // namespace logger
