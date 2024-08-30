#ifndef MODELS_HPP_

#define MODELS_HPP_

#include "../../HttpServerExceptions.hpp"
#include <map>
#include <string>
// Abstract Model interface
class Model {
  public:
    virtual std::map<std::string, std::string>
    convertToMap() const = 0;
    virtual std::string toString() const = 0;
};
class Patient : public Model {
  public:
    Patient() = delete;
    Patient(const int id, const std::string name)
        : id_(id), name_(name)
    {
    }

    std::map<std::string, std::string>
    convertToMap() const override
    {
        return std::map<std::string, std::string>{
            { "id", std::to_string(id_) }, { "name", name_ }
        };
    }

    int
    getId() const
    {
        return id_;
    }
    std::string
    getName() const
    {
        return name_;
    }

    std::string
    toString() const override
    {
        return "Patient | ID : " + std::to_string(id_)
               + " | NAME : " + name_;
    }

  private:
    const int id_;
    const std::string name_;
};

// Parses std::map and attempts to map the contents to
// Database models
class SQLiteMapper {
  public:
    static Patient
    createPatient(
        const std::map<std::string, std::string> &rowData)
    {
        // Validation
        if (rowData.find("id") == rowData.cend()
            && rowData.find("name") == rowData.cend()) {
            throw database_error(
                "Conversion from SQL row to Patient object "
                "failed. Row has incomplete columns.");
        }

        // Conversions
        int id = std::stoi(rowData.at("id"));
        std::string name{ rowData.at("name") };

        return Patient(id, name);
    }

  private:
};

#endif // !MODELS_HPP_
