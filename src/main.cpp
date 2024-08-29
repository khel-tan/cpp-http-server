#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>

#include "handlers/hospital/AddPatientHandler.hpp"
#include "handlers/hospital/GetPatientsHandler.hpp"
#include "message/URI.hpp"
#include "parser/IterativeParser.hpp"
#include "server/HttpServer.hpp"
#include "services/hospital/HospitalDatabase.hpp"
#include "services/hospital/models.hpp"
#include "socket/TCPSocket.hpp"

int parsePort(const char *arg, const int DEFAULT);

int
main(int argc, char **argv)
{
    const int DEFAULT_PORT = 5100;
    const int PORT = argc > 1
                         ? parsePort(argv[1], DEFAULT_PORT)
                         : DEFAULT_PORT;

    HttpServer server(std::make_unique<TCPSocket>(PORT),
                      std::make_unique<IterativeParser>());
    auto db = std::make_shared<HospitalDatabase>(
        "./hospital.db");
    server.mapHandler(
        URI("/hospital/add"),
        std::make_unique<AddPatientHandler>(db));
    server.mapHandler(
        URI("/hospital/patients"),
        std::make_unique<GetPatientHandler>(db));

    server.run();
}

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
