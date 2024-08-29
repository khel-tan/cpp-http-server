#ifndef GET_PATIENT_HANDLER_HPP_
#define GET_PATIENT_HANDLER_HPP_

#include "HospitalDBHandler.hpp"
#include <memory>

class GetPatientHandler : public HospitalDBHandler {
  public:
    GetPatientHandler() = delete;
    GetPatientHandler(std::shared_ptr<HospitalDatabase> db)
        : HospitalDBHandler(db)
    {
    }

  protected:
    void processRequestLine(const Request &) override;
    void processHeaders(const Request &) override;

    void
    processRequestBody(const std::string &body) override;
    void constructResponseBody() override;
};
#endif
