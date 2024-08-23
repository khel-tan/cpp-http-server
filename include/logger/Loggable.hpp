#ifndef LOGGABLE_HPP_
#define LOGGABLE_HPP_

#include "Logger.hpp"
#include <memory>

namespace logger {
class Loggable {
public:
  virtual ~Loggable() = 0;
  virtual void log() const = 0;

protected:
  std::shared_ptr<logger::Logger> logger_;
};
}; // namespace logger

#endif // !LOGGABLE_HPP_
