
#ifndef DELETE_PATIENT_HANLDER_HPP_

#define DELETE_PATIENT_HANLDER_HPP_

#include "HospitalDBHandler.hpp"
#include <string>

/**
 * @brief Deletes a patient entry by id
 */
class DeletePatientHandler : public HospitalDBHandler {

  public:
    DeletePatientHandler() = delete;
    DeletePatientHandler(
        std::shared_ptr<HospitalDatabase> db)
        : HospitalDBHandler(db)
    {
    }

  protected:
    /**
     * @brief Ensures that we have only DELETE requests
     * @param request request to be processed
     */
    void
    processRequestLine(const Request &request) override
    {
        if (request.getMethod() != Method::DELETE) {
            throw invalid_request(
                "Only DELETE requests are accepted!");
        }

        builder_.setVersion(request.getVersion());
        builder_.setStatusCode(StatusCode::OK);
    }
    void
    processHeaders(const Request &request) override
    {
    }

    /**
     * @brief Checks if the request body is a JSON and
     * has an id field. If so, we update the corresponding
     * entry in the database
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

        db_->deletePatient(std::stoi(m.at("id")));
    }
    void
    constructResponseBody() override
    {
    }
};

#endif // !DELETE_PATIENT_HANLDER_HPP_
