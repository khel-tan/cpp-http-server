#ifndef ADD_PATIENT_HANDLER_HPP_

#define ADD_PATIENT_HANDLER_HPP_

#include "../Handler.hpp"
class AddPatientHandler : public Handler {
    Response handleRequest(const Request &) override;
};

#endif // !ADD_PATIENT_HANDLER_HPP_
