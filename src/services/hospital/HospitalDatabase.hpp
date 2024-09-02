#ifndef HOSPITAL_DATABASE_HPP_
#define HOSPITAL_DATABASE_HPP_

#include "../SQLDatabase.hpp"
#include "models.hpp"
#include <vector>

/**
 * @brief Wrapper class that handle requests to the SQLite3
 * database and wraps it in an API that avoids unsafe C
 * constructs
 */
class HospitalDatabase : public SQLDatabase {
  public:
    HospitalDatabase() = delete;
    HospitalDatabase(const std::string filePath)
        : SQLDatabase(filePath)
    {

        initialize();
    }
    /**
     * @brief Add the data of a new patient
     */
    void addPatient(const Patient &);
    /**
     * @brief Update the data of a patient by id
     */
    void updatePatient(const int id, const Patient &);
    /**
     * @brief Get a list of all patients
     */
    std::vector<Patient> getPatients();
    /**
     * @brief Delete a patient entry by id
     */
    void deletePatient(const int id);

  protected:
    const std::string PATIENT_TABLE{ "PATIENTS" };

    /**
     * @brief Check if tables we want exist and initialize
     * them if not
     */
    void initialize() override;
};
#endif // !HOSPITAL_DATABASE_HPP_
