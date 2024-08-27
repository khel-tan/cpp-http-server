#ifndef SQL_DATABASE_HPP_

#define SQL_DATABASE_HPP_

#include <filesystem>
#include <iostream>
#include <sqlite3.h>
#include <stdexcept>

/*
 * Abstract class that wraps around C API for sqlite3
 * It provides an implementation of
 */
class SQLDatabase {
  protected:
    sqlite3 *db_;
    std::string filePath_;
    bool
    fileExists() const
    {
        return std::filesystem::exists(filePath_);
    }
    void
    closeConnection()
    {
        sqlite3_close(db_);
        db_ = nullptr;
    }

    // WARN: This method interacts with the C API and is
    // potentially unsafe!
    void
    startConnection()
    {
        char *errorMsg;
        int returnCode
            = sqlite3_open(filePath_.c_str(), &db_);

        if (returnCode != 0) {
            throw std::runtime_error(
                "Database connection failed!");
        }
    }
    void
    runQuery(const std::string &cmd) const
    {
        char *errMsg = 0;
        int returnCode
            = sqlite3_exec(db_, cmd.c_str(), 0, 0, &errMsg);

        if (returnCode != SQLITE_OK) {
            sqlite3_free(errMsg);
            throw std::runtime_error("Query failed");
        }
    }

    virtual void initialize() = 0;

  public:
    SQLDatabase() = delete;
    SQLDatabase(const std::string filePath)
        : filePath_(filePath)
    {
        startConnection();
    }
    virtual ~SQLDatabase() { closeConnection(); }

    virtual void reset() = 0;
};
/*static int
callback(void *data, int argc, char **argv,
         char **azColName)
{
    for (int i = 0; i < argc; i++) {
        std::cout << azColName[i] << " = "
                  << (argv[i] ? argv[i] : "NULL")
                  << std::endl;
    }
    std::cout << std::endl;
    return 0;
}
class SQLDatabase {
  protected:
    sqlite3 *db;

  public:
    SQLDatabase() = delete;
    SQLDatabase(std::string dbPath) {}
    ~SQLDatabase() { sqlite3_close(db); }
    int
    test()
    {
        sqlite3 *db;
        char *errMessage = 0;
        int rc;
        rc = sqlite3_open("./test.db", &db);
        if (rc) {
            std::cerr << "Can't open database: "
                      << sqlite3_errmsg(db) << std::endl;
            return rc;
        }
        else {
            std::cout << "Opened database successfully"
                      << std::endl;
        }
        const char *createTableSQL
            = "CREATE TABLE IF NOT EXISTS my_table (id "
              "INTEGER PRIMARY KEY AUTOINCREMENT, name "
              "TEXT NOT NULL);";
        rc = sqlite3_exec(db, createTableSQL, 0, 0,
                          &errMessage);
        if (rc != SQLITE_OK) {
            std::cerr << "SQL error: " << errMessage
                      << std::endl;
            sqlite3_free(errMessage);
        }
        else {
            std::cout << "Table created successfully"
                      << std::endl;
        }

        // Insert data into the table
        const char *insertDataSQL
            = "INSERT INTO my_table (name) VALUES "
              "('Alice');";
        rc = sqlite3_exec(db, insertDataSQL, 0, 0,
                          &errMessage);
        if (rc != SQLITE_OK) {
            std::cerr << "SQL error: " << errMessage
                      << std::endl;
            sqlite3_free(errMessage);
        }
        else {
            std::cout << "Data inserted successfully"
                      << std::endl;
        }

        // Query data from the table
        const char *selectSQL = "SELECT * FROM my_table;";
        rc = sqlite3_exec(db, selectSQL, callback, 0,
                          &errMessage);
        if (rc != SQLITE_OK) {
            std::cerr << "SQL error: " << errMessage
                      << std::endl;
            sqlite3_free(errMessage);
        }
        else {
            std::cout << "Query executed successfully"
                      << std::endl;
        }

        // Close the database connection
        sqlite3_close(db);

        return 0;
    }
};
*/
#endif // !SQL_DATABASE_HPP_
