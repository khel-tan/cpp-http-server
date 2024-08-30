#include "GetPatientsHandler.hpp"
#include "../../HttpServerExceptions.hpp"
#include <stdexcept>
#include <string>

void
GetPatientHandler::processRequestLine(
    const Request &request)
{
    if (request.getMethod() != Method::GET) {
        throw InvalidRequest(
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
      htmlBody += "<h1>Patient " + std::to_string(p.getId())
                  + "</h1>";
      htmlBody += "<span>Name: " + p.getName() + "</span>";
  }
  // clang-format off
  htmlBody += R"(</body></html>)";

  builder_.setBody(htmlBody);
  builder_.setHeaders("Content-Length", std::to_string(htmlBody.size()));
  builder_.setHeaders("Content-Type", "text/html");
}


