
#ifndef SQL_DATABASE_HPP_

#define SQL_DATABASE_HPP_

#include <iostream>
#include <map>
#include <numeric>
#include <ranges>
#include <sqlite3.h>
#include <stdexcept>
#include <string>
class SQLDatabase {
  public:
    SQLDatabase() = delete;
    SQLDatabase(const std::string filePath)
        : filePath_(filePath)
    {
        startConnection();
    }
    virtual ~SQLDatabase() { closeConnection(); }

  protected:
    const std::string filePath_;
    sqlite3 *db_;

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
        std::cout << cmd << std::endl;
        char *errMsg = 0;
        int returnCode
            = sqlite3_exec(db_, cmd.c_str(), 0, 0, &errMsg);

        if (returnCode != SQLITE_OK) {
            std::cout << errMsg << std::endl;
            sqlite3_free(errMsg);
            throw std::runtime_error("Query failed");
        }
    }
    std::string
    mapToQueryArguments(
        const std::map<std::string, std::string> &m)

    {
        auto parametersFold = [](std::string acc,
                                 std::string param) {
            return acc.empty() ? param : acc + ',' + param;
        };
        auto argumentsFold = [](const std::string &acc,
                                const std::string &arg) {
            auto argWithQuotes = '\'' + arg + '\'';
            return acc.empty() ? argWithQuotes
                               : acc + ',' + argWithQuotes;
        };
        auto keys = std::views::keys(m);
        auto values = std::views::values(m);
        std::string parameters = std::accumulate(
            keys.begin(), keys.end(), std::string{},
            parametersFold);
        std::string arguments
            = std::accumulate(values.begin(), values.end(),
                              std::string{}, argumentsFold);
        std::string query = "(" + parameters + ") VALUES ("
                            + arguments + ")";
        return query;
    }
    virtual void initialize() = 0;
};
#endif
