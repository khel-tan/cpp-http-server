#ifndef HOSPITAL_DATABASE_HPP_

#define HOSPITAL_DATABASE_HPP_

#include "../SQLDatabase.hpp"
#include "models/Patient.hpp"
class HospitalDatabase : public SQLDatabase {
  public:
    HospitalDatabase() = delete;
    HospitalDatabase(const std::string filePath)
        : SQLDatabase(filePath)
    {
        initialize();
    }
    void insertPatient(const Patient &) const;
    void reset() override;
    void test() const;

  protected:
    void initialize() override;
};

#endif // !HOSPITAL_DATABASE_HPP_
