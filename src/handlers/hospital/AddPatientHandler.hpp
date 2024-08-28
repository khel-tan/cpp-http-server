#ifndef ADD_PATIENT_HANDLER_HPP_

#define ADD_PATIENT_HANDLER_HPP_
#include "../../services/hospital/HospitalDatabase.hpp"

#include "../Handler.hpp"
#include <memory>
class AddPatientHandler : public Handler {
  public:
    AddPatientHandler() = delete;
    AddPatientHandler(std::shared_ptr<HospitalDatabase> db)
        : db_(db)
    {
    }
    Response handleRequest(const Request &) override;

  protected:
    std::shared_ptr<HospitalDatabase> db_;
    void validateRequest(const Request &) override;
    void validateBody(const std::string &body) override;
};

#endif //
