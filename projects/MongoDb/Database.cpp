#include "Database.hpp"

#define CHECK_DATABASE() \
        auto database = LUA->GetUserType<mongoc_database_t>(1, DatabaseMetaTableId); \
        if (database == nullptr) { \
            LUA->ThrowError("database is nullptr, did you forget to pass \"self\" with \":\" ?"); \
            return 0; \
        }

LUA_FUNCTION(destroy_database) {
    CHECK_DATABASE()

    mongoc_database_destroy(database);

    return 0;
}

LUA_FUNCTION(database_name) {
    CHECK_DATABASE()

    auto name = mongoc_database_get_name(database);

    LUA->PushString(name);

    return 1;
}

LUA_FUNCTION(database_copy) {
    CHECK_DATABASE()

    auto copy = mongoc_database_copy(database);

    LUA->PushUserType(copy, DatabaseMetaTableId);

    return 1;
}

LUA_FUNCTION(database_drop) {
    CHECK_DATABASE()

    bson_error_t error;
    bool success = mongoc_database_drop(database, &error);
    if (!success) {
        LUA->ThrowError(error.message);
    }

    LUA->PushBool(success);

    return 1;
}

LUA_FUNCTION(database_command) {
    CHECK_DATABASE()

    LUA->CheckType(2, GarrysMod::Lua::Type::Table);

    auto commandRef = LUA->ReferenceCreate();
    auto command = LuaToBSON(LUA, commandRef);
    LUA->ReferenceFree(commandRef);

    bson_t reply;
    bson_error_t error;
    bool success = mongoc_database_command_simple(database, command, nullptr, &reply, &error);

    if (!success) {
        LUA->ThrowError(error.message);
        return 0;
    }

    bson_destroy(command);

    auto resultRef = BSONToLua(LUA, &reply);

    LUA->ReferencePush(resultRef);

    return 1;
}

LUA_FUNCTION(database_write_command_with_opts) {
    CHECK_DATABASE()

    CHECK_BSON(command, opts)

    SETUP_QUERY(error, reply)

    bool success = mongoc_database_write_command_with_opts(database, command, nullptr, &reply, &error);

    CLEANUP_BSON(command, opts)

    CLEANUP_QUERY(error, reply, !success)

    auto resultRef = BSONToLua(LUA, &reply);
    LUA->ReferencePush(resultRef);

    return 1;
}

LUA_FUNCTION(database_user_add) {
    CHECK_DATABASE()


    auto username = LUA->CheckString(2);
    auto password = LUA->CheckString(3);

    int rolesRef = INT_MIN, dataRef = INT_MIN;

    if (LUA->Top() == 5) {
        if (LUA->IsType(4, GarrysMod::Lua::Type::Table) && LUA->IsType(5, GarrysMod::Lua::Type::Table)) {
            dataRef = LUA->ReferenceCreate();
            rolesRef = LUA->ReferenceCreate();
        } else if (LUA->IsType(5, GarrysMod::Lua::Type::Table)) {
            dataRef = LUA->ReferenceCreate();
        } else {
            LUA->ThrowError("Incorrect number of arguments passed!");
        }
    } else if (LUA->Top() == 4 && LUA->IsType(4, GarrysMod::Lua::Type::Table)) {
        rolesRef = LUA->ReferenceCreate();
    }

    bson_t* roles;
    if (rolesRef != INT_MIN) {
        roles = LuaToBSON(LUA, rolesRef);
        LUA->ReferenceFree(rolesRef);
    }

    bson_t* data;
    if (dataRef != INT_MIN) {
        data = LuaToBSON(LUA, dataRef);
    }

    bson_error_t error;
    bool success = mongoc_database_add_user(database, username, password, roles, data, &error);

    if (rolesRef != INT_MIN) {
        LUA->ReferenceFree(rolesRef);
        bson_destroy(roles);
    }

    if (dataRef != INT_MIN) {
        LUA->ReferenceFree(dataRef);
        bson_destroy(data);
    }

    LUA->PushBool(success);

    return 1;
}

LUA_FUNCTION(database_user_remove) {
    CHECK_DATABASE()

    auto username = LUA->CheckString(2);

    bson_error_t error;
    bool success = mongoc_database_remove_user(database, username, &error);
    if (error.code != 0) {
        LUA->ThrowError(error.message);
        return 0;
    }

    LUA->PushBool(success);

    return 1;
}

LUA_FUNCTION(database_collection_exists) {
    CHECK_DATABASE()

    auto name = LUA->CheckString(2);

    bson_error_t error;
    bool exists = mongoc_database_has_collection(database, name, &error);
    if (error.code != 0) {
        LUA->ThrowError(error.message);
        return 0;
    }

    LUA->PushBool(exists);

    return 1;
}

LUA_FUNCTION(database_collection_get) {
    CHECK_DATABASE()

    auto name = LUA->CheckString(2);

    auto collection = mongoc_database_get_collection(database, name);

    LUA->PushUserType(collection, CollectionMetaTableId);

    return 1;
}

LUA_FUNCTION(database_collection_create) {
    CHECK_DATABASE()

    auto name = LUA->CheckString(2);

    bson_t* options;
    if (LUA->IsType(3, GarrysMod::Lua::Type::Table)) {
        int optionsRef = LUA->ReferenceCreate();
        options = LuaToBSON(LUA, optionsRef);
    }

    bson_error_t error;
    auto collection = mongoc_database_create_collection(database, name, options, &error);

    LUA->PushUserType(collection, CollectionMetaTableId);

    return 1;
}
