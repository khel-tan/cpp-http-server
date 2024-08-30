
#ifndef DELETE_PATIENT_HANLDER_HPP_

#define DELETE_PATIENT_HANLDER_HPP_

#include "../../library/nlohmann/json.hpp"
#include "HospitalDBHandler.hpp"
#include <string>

class DeletePatientHandler : public HospitalDBHandler {

  public:
    DeletePatientHandler() = delete;
    DeletePatientHandler(
        std::shared_ptr<HospitalDatabase> db)
        : HospitalDBHandler(db)
    {
    }

  protected:
    void
    processRequestLine(const Request &request) override
    {
        if (request.getMethod() != Method::DELETE) {
            throw InvalidRequest(
                "Only DELETE requests are accepted!");
        }

        builder_.setVersion(request.getVersion());
        builder_.setStatusCode(StatusCode::OK);
    }
    void
    processHeaders(const Request &request) override
    {
    }

    void
    processRequestBody(const std::string &body) override
    {
        using json = nlohmann::json;
        try {
            json data = json::parse(body);
            auto m = data.get<
                std::map<std::string, std::string> >();

            if (!m.contains("id")) {
                throw InvalidRequestBody(
                    "Update request does not contain "
                    "patient id");
            }

            db_->deletePatient(std::stoi(m.at("id")));
        }
        catch (json::exception) {
            throw InvalidRequestBody(
                "Invalid request body");
        }
    }
    void
    constructResponseBody() override
    {
    }
};

#endif // !DELETE_PATIENT_HANLDER_HPP_
