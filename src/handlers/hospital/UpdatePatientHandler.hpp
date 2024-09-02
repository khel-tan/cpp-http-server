#ifndef UPDATE_PATIENT_HANLDER_HPP_

#define UPDATE_PATIENT_HANLDER_HPP_

#include "../../library/nlohmann/json.hpp"
#include "HospitalDBHandler.hpp"

class UpdatePatientHandler : public HospitalDBHandler {

  public:
    UpdatePatientHandler() = delete;
    UpdatePatientHandler(
        std::shared_ptr<HospitalDatabase> db)
        : HospitalDBHandler(db)
    {
    }

  protected:
    /**
     * @brief Ensures that the request type is PATCH
     */
    void
    processRequestLine(const Request &request) override
    {
        if (request.getMethod() != Method::PATCH) {
            throw invalid_request(
                "Only Patch requests are accepted!");
        }

        builder_.setVersion(request.getVersion());
        builder_.setStatusCode(StatusCode::OK);
    }
    /**
     * @brief We do nothing here
     */
    void
    processHeaders(const Request &request) override
    {
    }

    /**
     * @brief Ensures that the body is JSON and has an id
     * to identify the patient data. If valid, we update the
     * data.
     */
    void
    processRequestBody(const std::string &body) override
    {
        auto m = parseBody(body);
        if (!m.contains("id")) {
            throw invalid_request_body(
                "Update request does not contain "
                "patient id");
        }

        auto patient = SQLiteMapper::createPatient(m);
        db_->updatePatient(std::stoi(m.at("id")), patient);
    }
    /**
     * @brief PATCH requests needs no data back hence no
     * body
     */
    void
    constructResponseBody() override
    {
    }
};

#endif // !UPDATE_PATIENT_HANLDER_HPP_
