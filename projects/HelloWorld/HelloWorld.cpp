#include "GarrysMod/Lua/Interface.h"
#include <mongoc.h>
// Tests importing mongo-c-driver. Module should be require'd in gmod server without error
/*
	require "HelloWorld"
	print( TestFunction( 5, 17 ) )
*/

using namespace GarrysMod::Lua;

LUA_FUNCTION( MyExampleFunction )
{
	double first_number = LUA->CheckNumber( 1 );
	double second_number = LUA->CheckNumber( 2 );

	LUA->PushNumber( first_number + second_number );
	return 1;
}

GMOD_MODULE_OPEN()
{
	mongoc_init();
	LUA->PushSpecial( GarrysMod::Lua::SPECIAL_GLOB );
	LUA->PushString( "TestFunction" );
	LUA->PushCFunction( MyExampleFunction );
	LUA->SetTable( -3 ); // `_G.TestFunction = MyExampleFunction`

	return 0;
}

GMOD_MODULE_CLOSE()
{
	mongoc_cleanup();
	return 0;
}