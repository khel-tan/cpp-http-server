#ifndef SERVER_HPP_

#define SERVER_HPP_

/**
 * @brief Abstract server with run() performing some service
 */
class Server {
  public:
    virtual ~Server() = default;
    /**
     * @brief Start providing whatever services that we are
     * supposed to provide
     */
    virtual void run() = 0;
};

#endif // !SERVER_HPP_
