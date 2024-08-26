#include "AddPatientHandler.hpp"
#include <stdexcept>

Response
AddPatientHandler::handleRequest(const Request &request)
{
    auto builder = Response::getBuilder().setVersion(
        request.getVersion());
    if (request.getMethod() != Method::POST) {
        builder.setStatusCode(StatusCode::BAD_REQUEST);
        return builder.build();
    }

    return builder.setStatusCode(StatusCode::OK).build();
}
