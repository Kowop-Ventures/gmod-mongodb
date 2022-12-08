cmake_minimum_required (VERSION 3.13)

find_package(mongoc-1.0 CONFIG REQUIRED)

set(SOURCES
	Basic.cpp)

add_executable( Basic ${SOURCES})

target_include_directories(Basic PRIVATE ${MONGOC_STATIC_INCLUDE_DIRS})

target_link_libraries(Basic PRIVATE mongo::mongoc_static)