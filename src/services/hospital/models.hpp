#ifndef MODELS_HPP_

#define MODELS_HPP_

#include <map>
#include <stdexcept>
#include <string>
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

class SQLiteMapper {
  public:
    static Patient
    createPatient(
        const std::map<std::string, std::string> &rowData)
    {
        // Validation
        if (rowData.find("id") == rowData.cend()
            && rowData.find("name") == rowData.cend()) {
            throw std::invalid_argument(
                "SQL row has incomplete data for patient "
                "type");
        }

        // Conversions
        int id = std::stoi(rowData.at("id"));
        std::string name{ rowData.at("name") };

        return Patient(id, name);
    }

  private:
};

#endif // !MODELS_HPP_
