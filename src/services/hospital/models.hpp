#ifndef MODELS_HPP_

#define MODELS_HPP_

#include "../../HttpServerExceptions.hpp"
#include <map>
#include <string>
/**
 * @brief Abstract class that defines the basic structure of
 * every SQL row entry
 */
class Model {
  public:
    /**
     * @brief Converts model object to a key-value map of
     * its properties
     */
    virtual std::map<std::string, std::string>
    convertToMap() const = 0;
    /**
     * @brief converts the instance to a printable string
     */
    virtual std::string toString() const = 0;
};
/**
 * @brief Represents the encapsulated data of a patient
 */
class Patient : public Model {
  public:
    Patient() = delete;
    /**
     * @brief Constructor to initialize all members of
     * Patient
     * @param id identifier number of the patient
     * @param name name of the patient
     */
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

    /**
     * @brief Gets patient id
     */
    int
    getId() const
    {
        return id_;
    }
    /**
     * @brief Gets patient name
     */
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
/**
 * @brief Utility class for mapping std::map to
 * an instance of Model
 */
class SQLiteMapper {
  public:
    /**
     * @brief create a patient from a key-value map
     *
     * It throws an error if all the keys we need to make
     * Patient are not present.
     *
     * @return a Patient object
     */
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
};

#endif // !MODELS_HPP_
