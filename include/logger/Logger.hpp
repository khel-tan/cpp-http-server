#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <string>
namespace logger {

enum class LogLevel { DEBUG, INFO, WARNING, ERROR, CRITICAL };
enum class OutputType { CONSOLE, FILE };
class Logger {
public:
  static Logger &getInstance();
  void log(const std::string &message, LogLevel level);
  void setOutput(OutputType output);

  ~Logger() = default;
  // Delete move, copy and their corresponding assignment constructors
  Logger(const Logger &) = delete;
  Logger &operator=(const Logger &) = delete;

  Logger(Logger &&) = delete;
  Logger &operator=(Logger &&) = delete;

private:
  Logger();
};
}; // namespace logger
#endif
