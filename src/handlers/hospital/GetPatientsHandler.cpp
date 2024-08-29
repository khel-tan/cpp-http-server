#include "GetPatientsHandler.hpp"
#include <stdexcept>

void
GetPatientHandler::processRequestLine(
    const Request &request)
{
    if (request.getMethod() != Method::GET) {
        throw std::invalid_argument(
            "Invalid method for this endpoint!");
    }

    builder_.setVersion(request.getVersion());
    builder_.setStatusCode(StatusCode::OK);
}

void
GetPatientHandler::processHeaders(const Request &request)
{
}

void
GetPatientHandler::processRequestBody(
    const std::string &body)
{
}

void
GetPatientHandler::constructResponseBody()
{
  std::string htmlBody = R"(
    <!DOCTYPE html>
    <html>
    <head>
    </head>
    <body>)";
  for(const auto& p: db_->getPatients())
  {
      htmlBody += "<h1>" + p.toString() + "</h1>";
  }
  // clang-format off
  htmlBody += R"(</body></html>)";

  builder_.setBody(htmlBody);
}


