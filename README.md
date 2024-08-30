## Table of Contents
- [Implemented features](#features)
- [How to navigate the project](#navigation)
  - [Overview](#overview)
- [How to run](#how-to-run)
- [Libraries used](#Libraries-used)

## Features

## Navigation
### Overview
The flow of the program is as follows.

In `main.cpp`, an instance of the HTTP server is created and its dependencies are injected. Afterwards, we map URI objects to their corresponding HTTP request handlers so that they are handled appropriately.

The server has one main method - `run()`.
In this method, HttpServer directs the data flow from its network socket to the request parser and then redirects the transmittable data string of the Response object provided by the corresponding handler over the socket.

The server is dependent on 3 interfaces - Socket, RequestParser and Handler.
In addition, the entire flow of data is dependent on the HTTP Message/Request/Response classes.

### Socket
Socket manages the inflow and outflow of data over the network and provides a nice wrapper interface using std::string. TCPSocket, the implementation I used uses the C API from socket.h to set up the server socket, listen, connect to a client socket, and receive or transmit data streams.

### RequestParser
Request parser receives some string input and builds a (HTTP) Request object from it. The implementation I have provided - Iterative parser - parses the request line, headers and the body, and builds the Request.

### Handler
A Handler receives a (HTTP) Request object as its input and returns an HTTP Response object.

### HTTP Message/Request/Response classes
Both Request and Response classes inherit the abstract Message class which contains features common to both. Instances of both classes are accessible only through their builder interface which is exposed through the getBuilder() methods. In addition to fluent construction, the builder interface provides validation of Request objects so that for example, we do not create a response with no status code.
Status codes, request types and HTTP versions are encapsulated in their respective enum classes.

Moreover, to demonstrate the functionality of the server, I have added a minimal hospital list of records of patients. It is dependent on HospitalDatabase which inherits from SQLDatabase. It essentially encapsulates the C API of SQLite3 so that the users of the class can simply call methods such as `getPatients()` instead of doing memory management or writing queries.

## How to run

If you are on Linux, there is a build script in the `bin` subdirectory.
Simply run `bin/run.sh` from the root of the project.
You can add an argument to the above command to specify the port at which the server listens. The default is 5100.

If you are unable to do the above, you can just build from `CMakeLists.txt` at the root.

There is a simple Hospital Database running on top of the server infrastructure. To test it, simply run the application and send HTTP requests to the `localhost:[PORT]`. If localhost does not work, try `0.0.0.0:[PORT]`.

The following endpoints are supported at the moment.
- /hospital/patients : GET request
- /hospital/patients/add : POST request with {"id" : "some string", "name": "some name"} as the body
- /hospital/update : PATCH request with the body template as above
- /hospital/delete : DELETE request with {"id" : "some string"}

Currently, you can pass only strings for JSON values. This means that you cannot pass {"id" : 15} but {"id" : "15"}. If you do the former, the server will treat it as a malformed request.

### Examples
For testing the hospital database, you can use an API testing client such as Postman or Insomnia but passing the output through something like netcat is also viable. See the shell commands below for some examples.

`echo -e "GET /hospital/patients HTTP/1.1\r\nHost : Phone\r\n\r\n"| nc localhost [PORT]`

`echo -e "POST /hospital/patients/add HTTP/1.1\r\nHost : Phone\r\n\r\n{\"id\": \"125\", \"name\":\"Jack\"}\r\n"| nc localhost [PORT]`

`echo -e "PATCH /hospital/patients/update HTTP/1.1\r\nHost : Phone\r\n\r\n{\"id\": \"125\", \"name\":\"JackButCooler\"}\r\n"| nc localhost [PORT]`

`echo -e "DELETE /hospital/patients/delete HTTP/1.1\r\nHost : Phone\r\n\r\n{\"id\": \"125\"}\r\n"| nc localhost [PORT]`

## Libraries used
At present, the only 3rd party library used is [Nlohmann's JSON parser](https://github.com/nlohmann/json).
