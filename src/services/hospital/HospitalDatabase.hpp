#ifndef HOSPITAL_DATABASE_HPP_
#define HOSPITAL_DATABASE_HPP_

#include "../SQLDatabase.hpp"
#include "models.hpp"
#include <iostream>
#include <map>
#include <vector>

class HospitalDatabase : public SQLDatabase {
  public:
    HospitalDatabase() = delete;
    HospitalDatabase(const std::string filePath)
        : SQLDatabase(filePath)
    {

        initialize();
    }
    void addPatient(const Patient &);
    std::vector<Patient> getPatients();

  protected:
    const std::string PATIENT_TABLE{ "PATIENTS" };
    void initialize() override;
};
#endif // !HOSPITAL_DATABASE_HPP_
