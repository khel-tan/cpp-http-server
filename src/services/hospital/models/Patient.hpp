#ifndef PATIENT_HPP_

#define PATIENT_HPP_

#include <format>
#include <string>
class Patient {
  private:
    const int id_;
    const std::string name_;

  public:
    Patient() = delete;
    Patient(const int id, std::string name)
        : id_(id), name_(name)
    {
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
    };

    std::string
    toString() const
    {
        return std::format("Our esteemed customer {0}, "
                           "Identification number : {1}",
                           name_, id_);
    }
};

#endif // !PATIENT_HPP_
