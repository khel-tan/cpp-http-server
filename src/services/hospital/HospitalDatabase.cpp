#include "HospitalDatabase.hpp"
#include "models.hpp"
#include <vector>

void
HospitalDatabase::addPatient(const Patient &p)
{
    const std::string query
        = "INSERT INTO " + PATIENT_TABLE + " "
          + mapToQueryArguments(p.convertToMap()) + ";";
    runQuery(query);
}

std::vector<Patient>
HospitalDatabase::getPatients()
{
    sqlite3_stmt *statement;
    const char *query = "SELECT * FROM PATIENTS";

    std::vector<Patient> patients;
    int returnCode = sqlite3_prepare_v2(db_, query, -1,
                                        &statement, NULL);
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
