#ifndef ADD_PATIENT_HANDLER_HPP_

#define ADD_PATIENT_HANDLER_HPP_
#include "../../services/hospital/HospitalDatabase.hpp"

#include "HospitalDBHandler.hpp"
#include <memory>
class AddPatientHandler : public HospitalDBHandler {
  public:
    AddPatientHandler() = delete;
    AddPatientHandler(std::shared_ptr<HospitalDatabase> db)
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

#endif //
