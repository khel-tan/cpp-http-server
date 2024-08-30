
#ifndef SQL_DATABASE_HPP_

#define SQL_DATABASE_HPP_

#include "../HttpServerExceptions.hpp"
#include <iostream>
#include <map>
#include <numeric>
#include <ranges>
#include <sqlite3.h>
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
                "Database connection to " + filePath_
                + " failed!");
        }
    }

    // TODO: sqlite3_exec has security issues. Make it
    // safer.
    void
    runQuery(const std::string &cmd) const
    {
        char *errMsg = nullptr;
        int returnCode
            = sqlite3_exec(db_, cmd.c_str(), 0, 0, &errMsg);

        if (returnCode != SQLITE_OK) {
            sqlite3_free(errMsg);
            throw database_error("Query failed : " + cmd);
        }
    }
    std::string
    mapToQueryArguments(
        const std::map<std::string, std::string> &data)

    {
        auto parametersFold = [](const std::string &acc,
                                 const std::string &param) {
            return acc.empty() ? param : acc + ',' + param;
        };
        auto argumentsFold = [](const std::string &acc,
                                const std::string &arg) {
            auto argWithQuotes = '\'' + arg + '\'';
            return acc.empty() ? argWithQuotes
                               : acc + ',' + argWithQuotes;
        };
        auto keys = std::views::keys(data);
        auto values = std::views::values(data);
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
