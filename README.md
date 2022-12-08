# Mongodb lua module for Garry's Mod

Originally based on https://github.com/PolEpie/gmsv_mongodb

Includes:
* Upgraded mongo-c-driver to 1.17.1

# Installation

Copy the appropiate binary to `garrysmod\lua\bin`

Fow Windows:
Copy `gmsv_MongoDb_win64.dll` into `garrysmod\lua\bin`

# Usage
```lua
require('MongoDb')
local connectionString = 'mongodb+srv://<username>:<passwod>@cluster0.123456.mongodb.net'
local dbClient = mongodb.Client(connectionString, 'Harvest')
local database = dbClient:Database('main')
local playersCollection = database:GetCollection('player-connected')

gameevent.Listen( "player_connect" )
hook.Add("player_connect", "AnnounceConnection", function( data )
	print( data.name .. " has connected to the server." )
    playersCollection:Insert({
        steamid = data.networkid,
        name = data.name,
        steamid = data.networkid,
        userid = data.userid,
        bot = data.bot,
        connectedAt = os.date("!%Y-%m-%dT%TZ" , os.time())
    })
end)
```