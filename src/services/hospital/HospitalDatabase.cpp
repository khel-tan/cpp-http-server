#include "HospitalDatabase.hpp"
#include "models/Patient.hpp"
#include <stdexcept>
#include <string>
#include <vector>

void
HospitalDatabase::insertPatient(const Patient &p) const
{
    const std::string query
        = "INSERT INTO Patients (id, name) VALUES ("
          + std::to_string(p.getId()) + ", '" + p.getName()
          + "');";
    runQuery(query);
}

void
HospitalDatabase::reset()
{
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

std::vector<Patient>
HospitalDatabase::getPatients() const
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
        int id = sqlite3_column_int(statement, 0);
        std::string name
            = (const char *)sqlite3_column_text(statement,
                                                1);
        patients.push_back(Patient(id, name));
    }
    sqlite3_finalize(statement);
    return patients;
}
