#include "AddPatientHandler.hpp"
#include "../../library/nlohmann/json.hpp"
#include <iostream>
#include <stdexcept>

void
AddPatientHandler::processRequestLine(
    const Request &request)
{
    if (request.getMethod() != Method::POST) {
        throw std::invalid_argument(
            "Invalid method for this endpoint!");
    }

    builder_.setVersion(request.getVersion());
    builder_.setStatusCode(StatusCode::OK);
}

void
AddPatientHandler::processHeaders(const Request &request)
{
}

void
AddPatientHandler::processRequestBody(
    const std::string &body)
{
    // TODO: Throw invalid argument exception
    using json = nlohmann::json;
    try {
        json data = json::parse(body);
        auto m = data.get<
            std::map<std::string, std::string> >();
        auto patient = SQLiteMapper::createPatient(m);
        db_->addPatient(patient);
    }
    catch (json::exception) {
        throw std::invalid_argument("Invalid request body");
    }
}

void
AddPatientHandler::constructResponseBody()
{
}
