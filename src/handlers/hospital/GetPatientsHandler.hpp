#ifndef GET_PATIENT_HANDLER_HPP_
#define GET_PATIENT_HANDLER_HPP_

#include "HospitalDBHandler.hpp"
#include <memory>

/**
 * @brief Returns all the patient entries of the hospital
 */
class GetPatientHandler : public HospitalDBHandler {
  public:
    GetPatientHandler() = delete;
    GetPatientHandler(std::shared_ptr<HospitalDatabase> db)
        : HospitalDBHandler(db)
    {
    }

  protected:
    /**
     * @brief ensures that the method is GET
     *
     * @param request request to be processed
     */
    void
    processRequestLine(const Request &request) override
    {

        if (request.getMethod() != Method::GET) {
            throw invalid_request(
                "Invalid method for this endpoint!");
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
    }
    /**
     * @brief Constructs a short HTML file listing
     * each patient with their id and name and then sets
     * headers associated with content
     */
    void
    constructResponseBody() override
    {

      std::string htmlBody = R"(
        <!DOCTYPE html>
        <html>
        <head>
        </head>
        <body>)";
      for(const auto& p: db_->getPatients())
      {
          htmlBody += "<h1>Patient"
                      + std::to_string(p.getId()) + "</h1>";
          htmlBody
              += "<span>Name: " + p.getName() + "</span>";
      }
      // clang-format off
      htmlBody += R"(</body></html>)";

      builder_.setBody(htmlBody);
      builder_.setHeaders("Content-Length", std::to_string(htmlBody.size()));
      builder_.setHeaders("Content-Type", "text/html");
    }
};
#endif
