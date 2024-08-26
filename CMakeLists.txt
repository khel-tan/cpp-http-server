cmake_minimum_required(VERSION 3.10)
 
# Read the project name from config.txt
file(READ "${CMAKE_SOURCE_DIR}/config.txt" CONFIG_CONTENTS)
string(REGEX MATCH "PROJECT_NAME=([^\n]+)" _ ${CONFIG_CONTENTS})
set(PROJECT_NAME ${CMAKE_MATCH_1})

project(${PROJECT_NAME})
include_directories(include)

file(GLOB_RECURSE SOURCES "src/*.cpp")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
find_package(SQLite3 REQUIRED)
add_executable(${PROJECT_NAME} ${SOURCES})
if (SQLite3_FOUND)
  include_directories(${SQLite3_INCLUDE_DIRS})
  target_link_libraries(${PROJECT_NAME} ${SQLite3_LIBRARIES})
else()
  message(FATAL_ERROR "SQLite3 library not found.")
endif()
