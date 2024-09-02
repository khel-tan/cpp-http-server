#ifndef HOSPITAL_DB_HANDLER_HPP_
#define HOSPITAL_DB_HANDLER_HPP_

#include "../../HttpServerExceptions.hpp"
#include "../../library/nlohmann/json.hpp"
#include "../../services/hospital/HospitalDatabase.hpp"
#include "../Handler.hpp"
#include <memory>
/**
 * @brief This class ensures that all non-abstract handler
 * of the hospital database inherit the pointer to the
 * database
 */
class HospitalDBHandler : public Handler {
  public:
    /**
     * @brief Constructs a HospitalDBHandler from a
     * shared pointer to the database
     *
     * @param db shared pointer to the Hospital Database
     */
    HospitalDBHandler(std::shared_ptr<HospitalDatabase> db)
        : db_(db)
    {
    }

  protected:
    std::shared_ptr<HospitalDatabase> db_;
    /**
     * @brief Assuming it is JSON, parses the body of the
     * HTTP requests and constructs a key-value map
     *
     * If the JSON is invalid, throws an exception
     *
     * @param body The body of the HTTP request
     * @return A map from JSON keys to values
     *
     */
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
