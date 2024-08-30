#ifndef HOSPITAL_DB_HANDLER_HPP_
#define HOSPITAL_DB_HANDLER_HPP_

#include "../../HttpServerExceptions.hpp"
#include "../../library/nlohmann/json.hpp"
#include "../../services/hospital/HospitalDatabase.hpp"
#include "../Handler.hpp"
#include <memory>
class HospitalDBHandler : public Handler {
  public:
    HospitalDBHandler(std::shared_ptr<HospitalDatabase> db)
        : db_(db)
    {
    }

  protected:
    std::shared_ptr<HospitalDatabase> db_;
    std::map<std::string, std::string>
    parseBody(const std::string &body)
    {
        using json = nlohmann::json;
        try {
            auto data = json::parse(body);
            auto m = data.get<
                std::map<std::string, std::string> >();
            return m;
        }
        catch (json::exception) {
            throw invalid_request("Bad JSON");
        }
    }
};
#endif
