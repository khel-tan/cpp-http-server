#ifndef HOSPITAL_DB_HANDLER_HPP_
#define HOSPITAL_DB_HANDLER_HPP_

#include "../../services/hospital/HospitalDatabase.hpp"
#include "../Handler.hpp"
#include <memory>
class HospitalDBHandler : public Handler {
  public:
    HospitalDBHandler(std::shared_ptr<HospitalDatabase> db)
        : db_(db)
    {
    }

  protected:
    std::shared_ptr<HospitalDatabase> db_;
};
#endif
