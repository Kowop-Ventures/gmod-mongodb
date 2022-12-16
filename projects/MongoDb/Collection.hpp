#ifndef GMOD_MONGODB_COLLECTION_HPP
#define GMOD_MONGODB_COLLECTION_HPP

#include "MongoDB.hpp"

int destroy_collection(lua_State* state);

int collection_name(lua_State* state);

int collection_command(lua_State* state);

int collection_count(lua_State* state);

int collection_find(lua_State* state);

int collection_find_one(lua_State* state);

int collection_insert(lua_State* state);

int collection_remove(lua_State* state);

int collection_update_one(lua_State* state);

int collection_bulk(lua_State* state);

extern int CollectionMetaTableId;

#endif
