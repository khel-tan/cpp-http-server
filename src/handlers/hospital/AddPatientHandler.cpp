#include "AddPatientHandler.hpp"
#include "../../library/nlohmann/json.hpp"

Response
AddPatientHandler::handleRequest(const Request &request)
{

    builder_.setVersion(request.getVersion());
    if (request.getMethod() != Method::POST) {
        builder_.setStatusCode(StatusCode::BAD_REQUEST);
    }
    else {

        builder_.setStatusCode(StatusCode::OK);
    }
    validateBody(request.getBody());

    return builder_.build();
}

void
AddPatientHandler::validateRequest(const Request &request)
{
}
void
AddPatientHandler::validateBody(const std::string &body)
{
    using json = nlohmann::json;
    json data = json::parse(body);
    auto m
        = data.get<std::map<std::string, std::string> >();
    auto patient = SQLiteMapper::createPatient(m);
    db_->addPatient(patient);
}
