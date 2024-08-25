#ifndef TEST_HANDLER_
#define TEST_HANDLER_

#include "../message/Request.hpp"
#include "../message/Response.hpp"
#include "Handler.hpp"
class TestHandler : public Handler {
  public:
    Response
    handleRequest(const Request &request) override
    {
        auto builder = Response::getBuilder();
        return builder.setVersion(Version::HTTP_1_0)
            .setStatusCode(StatusCode::OK)
            .build();
    }
};
#endif
