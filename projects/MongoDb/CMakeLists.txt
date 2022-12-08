cmake_minimum_required (VERSION 3.13)

find_package(mongoc-1.0 CONFIG REQUIRED)

set(SOURCES
	MongoDB.cpp
	Client.hpp
	Client.cpp
	Util.cpp
	Util.hpp
	Database.cpp
	Database.hpp
	MongoDB.cpp
	MongoDB.hpp
	Collection.cpp
	Collection.hpp
	Bulk.cpp 
	Bulk.hpp 
	Macros.hpp 
	ObjectID.cpp 
	ObjectID.hpp
)

add_library(MongoDb SHARED ${SOURCES})


target_include_directories(MongoDb PRIVATE ${MONGOC_STATIC_INCLUDE_DIRS})

target_link_libraries(MongoDb PRIVATE mongo::mongoc_static)

target_link_libraries(MongoDb PRIVATE gmod-module-base)

set_gmod_suffix_prefix(MongoDb)