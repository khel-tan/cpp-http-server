#ifndef SOCKET_HPP_
#define SOCKET_HPP_
#include <vector>
class Socket {
public:
  virtual ~Socket() = default;
  virtual void acceptConnection() = 0;
  virtual std::vector<char> receiveData() = 0;
  virtual void closeSocket() = 0;
};
#endif // !SOCKET_HPP_
