#include "HospitalDatabase.hpp"
#include "models/Patient.hpp"
#include <string>

void
HospitalDatabase::insertPatient(const Patient &p) const
{
    const std::string query
        = "INSERT INTO Patients (name) VALUES ('"
          + p.getName() + "');";
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

void
HospitalDatabase::test() const
{
    sqlite3_stmt *statement;
    const char *query = "SELECT * FROM PATIENTS";
    int returnCode = sqlite3_prepare_v2(db_, query, -1,
                                        &statement, NULL);
    if (returnCode != SQLITE_OK) {
        std::cout << "Error" << std::endl;
        return;
    }
    while ((returnCode = sqlite3_step(statement))
           == SQLITE_ROW) {
        int id = sqlite3_column_int(statement, 0);
        const unsigned char *name
            = sqlite3_column_text(statement, 1);
        std::cout << "Printing row -> id : " << id
                  << " ,name : " << name << std::endl;
    }
    sqlite3_finalize(statement);
}
