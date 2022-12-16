# Creating an index

```lua
local client = mongodb.Client(connectionString, name)
local database = client:Database(dbName)

local result = database:WriteCommandWithOpts(
        {
            indexes = {
                {
                    key = { myKeyName = 1 },
                    name = "myKeyName_v0",
                    unique = true
                }
            },
            createIndexes = "my-collection-name"
        },
        {}
    )

PrintTable(result)
```

# Upsert a record
```lua
local data = ...
local selector =  {
    myKey = "1234"
}

local update = {
    ["$set"] = {
        createdAt = os.date("!%Y-%m-%dT%TZ" , os.time())
    },
    ["$setOnInsert"] = {
        myKey = data.myKey,
        myOtherKey = data.myOtherKey
    }
}
local opts = {
    upsert = true
}

myCollection:UpdateOne(selector, update, opts)
```