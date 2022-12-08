cmake_minimum_required (VERSION 3.13)

find_package(mongoc-1.0 CONFIG REQUIRED)

set(SOURCES
	HelloWorld.cpp)

add_library(HelloWorld SHARED ${SOURCES})

target_link_libraries(HelloWorld PRIVATE mongo::mongoc_static)

target_link_libraries(HelloWorld PRIVATE gmod-module-base)

set_gmod_suffix_prefix(HelloWorld)