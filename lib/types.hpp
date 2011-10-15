#ifndef LUA_TYPES_HPP
#define LUA_TYPES_HPP

#include <lua.hpp>

namespace lua
{
	enum Type
	{
		INVALID = LUA_TNONE, // For invalid stack indices
		NIL = LUA_TNIL,
		BOOLEAN = LUA_TBOOLEAN,
		NUMBER = LUA_TNUMBER,
		STRING = LUA_TSTRING,
		TABLE = LUA_TTABLE,
		FUNCTION = LUA_TFUNCTION,
		THREAD = LUA_TTHREAD,
		USERDATA = LUA_TUSERDATA,
		LIGHTUSERDATA = LUA_TLIGHTUSERDATA
	};

	Type convert_lua_type(const int& luaType);
}

#endif