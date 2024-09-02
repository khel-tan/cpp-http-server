#ifndef ADD_PATIENT_HANDLER_HPP_

#define ADD_PATIENT_HANDLER_HPP_
#include "../../services/hospital/HospitalDatabase.hpp"

#include "HospitalDBHandler.hpp"
#include <memory>
/**
 * @brief Handles the addition of a single patient together
 * with name and id
 *
 */

class AddPatientHandler : public HospitalDBHandler {
  public:
    AddPatientHandler() = delete;
    AddPatientHandler(std::shared_ptr<HospitalDatabase> db)
        : HospitalDBHandler(db)
    {
    }

  protected:
    /**
     * @brief Ensures that we accept only POST requests
     */
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
    /**
     * @brief irrelevant for this class
     */
    void
    processHeaders(const Request &) override
    {
    }

    /**
     * @brief parses id and patient data from the request
     * body and calls SQLiteMapper to create a patient
     * instance
     */
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
