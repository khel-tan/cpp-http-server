#include "../include/Logger.hpp"
#include <iostream>
#include <stdexcept>
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
Logger::~Logger() {}
