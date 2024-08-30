#include "HospitalDatabase.hpp"
#include "models.hpp"
#include <string>
#include <vector>

void
HospitalDatabase::addPatient(const Patient &p)
{
    const std::string query
        = "INSERT INTO " + PATIENT_TABLE + " "
          + mapToQueryArguments(p.convertToMap()) + ";";
    runQuery(query);
}

void
HospitalDatabase::updatePatient(const int id,
                                const Patient &p)
{
    const std::string query
        = "UPDATE " + PATIENT_TABLE + " SET name='"
          + p.getName()
          + "' WHERE id=" + std::to_string(id);
    runQuery(query);
}

void
HospitalDatabase::deletePatient(const int id)
{
    const std::string query
        = "DELETE FROM " + PATIENT_TABLE
          + " WHERE id=" + std::to_string(id);
    runQuery(query);
}

std::vector<Patient>
HospitalDatabase::getPatients()
{
    sqlite3_stmt *statement;
    const std::string query
        = "SELECT * FROM " + PATIENT_TABLE;

    std::vector<Patient> patients;
    int returnCode = sqlite3_prepare_v2(
        db_, query.c_str(), -1, &statement, NULL);
    if (returnCode != SQLITE_OK) {
        throw std::runtime_error("Query failed");
    }
    while ((returnCode = sqlite3_step(statement))
           == SQLITE_ROW) {
        std::string id = (const char *)sqlite3_column_text(
            statement, 0);
        std::string name
            = (const char *)sqlite3_column_text(statement,
                                                1);

        std::map<std::string, std::string> patientData{
            { "id", id }, { "name", name }
        };

        auto patient
            = SQLiteMapper::createPatient(patientData);
        patients.push_back(patient);
    }
    sqlite3_finalize(statement);
    return patients;
}

void
HospitalDatabase::initialize()
{
    // Initialize the tables if not already created
    const std::string CREATE_PATIENTS_TABLE
        = "CREATE TABLE IF NOT EXISTS PATIENTS(\
      id INTEGER PRIMARY KEY,\
      name TEXT NOT NULL\
        );";
    runQuery(CREATE_PATIENTS_TABLE);
}
