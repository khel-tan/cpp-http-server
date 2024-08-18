#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <string>
enum class LogLevel { DEBUG, INFO, WARNING, ERROR, CRITICAL };
enum class OutputType { CONSOLE, FILE };
class Logger {
public:
  static Logger &getInstance();
  void log(const std::string &message, LogLevel level);
  void setOutput(OutputType output);

  // Delete move, copy and their corresponding assignment constructors
  Logger(const Logger &) = delete;
  Logger &operator=(const Logger &) = delete;

  Logger(Logger &&) = delete;
  Logger &operator=(Logger &&) = delete;

private:
  Logger();
  ~Logger();
  // TODO: Delete move, move assignment, copy and copy assignment
};
#endif
