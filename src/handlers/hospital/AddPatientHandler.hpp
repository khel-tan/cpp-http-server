#ifndef ADD_PATIENT_HANDLER_HPP_

#define ADD_PATIENT_HANDLER_HPP_

#include "../Handler.hpp"
class AddPatientHandler : public Handler {
  public:
    Response handleRequest(const Request &) override;

  protected:
    void validateRequest(const Request &) override;
};

#endif // !ADD_PATIENT_HANDLER_HPP_
