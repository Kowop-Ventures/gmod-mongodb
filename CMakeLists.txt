cmake_minimum_required(VERSION 3.10)
project(gmod-module-base LANGUAGES CXX)

set(CMAKE_CONFIGURATION_TYPES Release Debug)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

message ("CMAKE_MODULE_PATH \"${CMAKE_MODULE_PATH}\"")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/bin/debug)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/bin/release)
set(CMAKE_RUNTIME_LIBRARY_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/bin/debug)
set(CMAKE_RUNTIME_LIBRARY_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/bin/release)

add_subdirectory(include)
add_subdirectory(projects/Basic)
add_subdirectory(projects/HelloWorld)
add_subdirectory(projects/MongoDb)