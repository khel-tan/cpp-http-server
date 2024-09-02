#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>

#include "handlers/hospital/AddPatientHandler.hpp"
#include "handlers/hospital/DeletePatientHandler.hpp"
#include "handlers/hospital/GetPatientsHandler.hpp"
#include "handlers/hospital/UpdatePatientHandler.hpp"
#include "message/URI.hpp"
#include "parser/IterativeParser.hpp"
#include "server/HttpServer.hpp"
#include "services/hospital/HospitalDatabase.hpp"
#include "socket/TCPSocket.hpp"

int parsePort(const char *arg, const int DEFAULT);

int
main(int argc, char **argv)
{
    constexpr int DEFAULT_PORT = 5100;
    const int PORT = argc > 1
                         ? parsePort(argv[1], DEFAULT_PORT)
                         : DEFAULT_PORT;

    HttpServer server(std::make_unique<TCPSocket>(PORT),
                      std::make_unique<IterativeParser>());
    auto db = std::make_shared<HospitalDatabase>(
        "./hospital.db");
    server.mapHandler(
        URI("/hospital/patients/list"),
        std::make_unique<GetPatientHandler>(db));
    server.mapHandler(
        URI("/hospital/patients/add"),
        std::make_unique<AddPatientHandler>(db));
    server.mapHandler(
        URI("/hospital/patients/update"),
        std::make_unique<UpdatePatientHandler>(db));
    server.mapHandler(
        URI("/hospital/patients/delete"),
        std::make_unique<DeletePatientHandler>(db));

    server.run();
}

/**
 * @brief parses port from arguments. If invalid, returns a
 * default port specified at compile time.
 * @return Port number
 */
int
parsePort(const char *arg, const int DEFAULT)
{
    try {
        return std::stoi(arg);
    }
    catch (std::invalid_argument) {
        return DEFAULT;
    }
}
