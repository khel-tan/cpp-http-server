#ifndef SERVER_HPP_

#define SERVER_HPP_

/*
 * Abstract server with run() performing some service
 */
class Server {
  public:
    virtual ~Server() = default;
    virtual void run() = 0;
};

#endif // !SERVER_HPP_
