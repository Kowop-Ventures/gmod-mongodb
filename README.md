# Mongodb lua module for Garry's Mod

Originally based on https://github.com/PolEpie/gmsv_mongodb

Includes:
* Upgraded mongo-c-driver to 1.17.1

Supported platforms:
* Windows x64
* Linux x64 (Ubuntu 20.04)

# Documentation

Please see articles in the [Wiki](https://github.com/chriswoodle/gmod-mongodb/wiki).

# Installation

Download the appropiate binary from [Releases](https://github.com/chriswoodle/gmod-mongodb/releases) into your `garrysmod\lua\bin` directory.

# Example

For more examples see [Usage](https://github.com/chriswoodle/gmod-mongodb/wiki/Usage)
```lua
require('mongodb')
local connectionString = 'mongodb+srv://<username>:<passwod>@cluster0.123456.mongodb.net'
local dbClient = mongodb.Client(connectionString, 'MyApplication')
local database = dbClient:Database('myDatabase')
local playersCollection = database:GetCollection('player-connected')

gameevent.Listen( "player_connect" )
hook.Add("player_connect", "AnnounceConnection", function( data )
	print( data.name .. " has connected to the server." )
    playersCollection:Insert({
        steamid = data.networkid,
        name = data.name,
        userid = data.userid,
        bot = data.bot,
        connectedAt = os.date("!%Y-%m-%dT%TZ" , os.time())
    })
end)
```