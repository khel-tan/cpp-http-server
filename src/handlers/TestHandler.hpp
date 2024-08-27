#ifndef TEST_HANDLER_
#define TEST_HANDLER_

#include "../message/Request.hpp"
#include "../message/Response.hpp"
#include "Handler.hpp"
#include <iostream>
class TestHandler : public Handler {
  public:
    Response
    handleRequest(const Request &request) override
    {
        std::cout << "Test handler at your service!"
                  << std::endl;
        auto builder = Response::getBuilder();
        return builder.setVersion(Version::HTTP_1_0)
            .setStatusCode(StatusCode::OK)
            .build();
    }

  protected:
    void
    validateRequest(const Request &) override
    {
    }
};
#endif
