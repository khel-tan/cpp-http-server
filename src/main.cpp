#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>

#include "handlers/TestHandler.hpp"
#include "handlers/hospital/AddPatientHandler.hpp"
#include "message/URI.hpp"
#include "parser/IterativeParser.hpp"
#include "server/HttpServer.hpp"
#include "services/hospital/HospitalDatabase.hpp"
#include "services/hospital/models/Patient.hpp"
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
    server.mapHandler(URI("/algorithms"),
                      std::make_unique<TestHandler>());
    server.mapHandler(
        URI("/hospital/add"),
        std::make_unique<AddPatientHandler>());
    server.run();

    // auto db = HospitalDatabase("./hospital.db");
    // db.insertPatient(Patient(0, "Mark"));
    // db.insertPatient(Patient(1, "Margaret"));
    // db.insertPatient(Patient(2, "Katherine"));
    // auto patients = db.getPatients();

    // for (const auto &p : patients) {
    //     std::cout << p.toString() << std::endl;
    // }
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
