#ifndef ADD_PATIENT_HANDLER_HPP_

#define ADD_PATIENT_HANDLER_HPP_
#include "../../services/hospital/HospitalDatabase.hpp"

#include "../../library/nlohmann/json.hpp"
#include "HospitalDBHandler.hpp"
#include <execution>
#include <memory>
class AddPatientHandler : public HospitalDBHandler {
  public:
    AddPatientHandler() = delete;
    AddPatientHandler(std::shared_ptr<HospitalDatabase> db)
        : HospitalDBHandler(db)
    {
    }

  protected:
    void
    processRequestLine(const Request &request) override
    {

        if (request.getMethod() != Method::POST) {
            throw invalid_request(
                "Invalid method for this endpoint!");
        }

        builder_.setVersion(request.getVersion());
        builder_.setStatusCode(StatusCode::CREATED);
    }
    void
    processHeaders(const Request &) override
    {
    }

    void
    processRequestBody(const std::string &body) override
    {
        auto m = parseBody(body);
        auto patient = SQLiteMapper::createPatient(m);
        db_->addPatient(patient);
    }
    void
    constructResponseBody() override
    {
    }
};

#endif //
