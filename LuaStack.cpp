#include "Lua.hpp"
#include "LuaStack.hpp"
#include "exceptions.hpp"

int LuaStack::invokeWrappedFunction(lua_State* state)
{
	void* p = lua_touserdata(state, lua_upvalueindex(1));
	ForwardingLuaFunction* func = static_cast<ForwardingLuaFunction*>(p);
	(*func)();
	return lua_gettop(state);
}

LuaStack::LuaStack(Lua& lua) :
	lua(lua),
	_offset(lua_gettop(lua.state))
{}

LuaStack& LuaStack::offset(int offset)
{
	if(offset < 0)
		throw LuaException(lua, "Offset must be non-negative");
	if(offset > lua_gettop(lua.state))
		throw LuaException(lua, "Offset must be less than the top of lua's stack");
	_offset = offset;
	return (*this);
}

int LuaStack::size() const
{
	return lua_gettop(lua.state) - offset();
}

LuaStack& LuaStack::pop(int count)
{
	if(count > size())
		throw LuaException(lua, "Refusing to pop elements not managed by this stack");
	lua_pop(lua.state, count);
	return (*this);
}

LuaStack& LuaStack::replace(int pos)
{
	checkPos(pos);
	if (empty())
		throw LuaException(lua, "Stack must not be empty when replacing elements");
	lua_replace(lua.state, pos);
	return (*this);
}

bool LuaStack::isMagicalPos(const int& pos) const
{
	return pos == LUA_GLOBALSINDEX;
}

void LuaStack::checkPos(int pos) const
{
	if (isMagicalPos(pos))
		return;
	const int top=lua_gettop(lua.state);
	if (pos == 0)
		throw LuaException(lua, "Stack position must not be zero");
	// Convert relative positions to absolute ones.
	if (pos < 0)
		pos += top;
	if (pos < offset())
		throw LuaException(lua, "Stack position is not managed by this stack");
	if (pos > top)
		throw LuaException(lua, "Stack position is beyond the top of the lua stack");
}

lua::Type LuaStack::type(int pos) const
{
	checkPos(pos);
	switch (lua_type(lua.state, pos)) {
		case LUA_TNIL:			return lua::Type::NIL;
		case LUA_TBOOLEAN:		return lua::Type::BOOLEAN;
		case LUA_TNUMBER:		return lua::Type::NUMBER;
		case LUA_TSTRING:		return lua::Type::STRING;
		case LUA_TTABLE:		return lua::Type::TABLE;
		case LUA_TFUNCTION:		return lua::Type::FUNCTION;
		case LUA_TTHREAD:		return lua::Type::THREAD;
		case LUA_TUSERDATA:		return lua::Type::USERDATA;
		case LUA_TLIGHTUSERDATA:	return lua::Type::LIGHTUSERDATA;
		default:			return lua::Type::INVALID;
	}
}

string LuaStack::typestring(int pos) const
{
	return std::string(lua_typename(lua.state, this->type(pos)));
}

LuaStack& LuaStack::to(const char*& sink, int pos)
{
	checkPos(pos);
	sink = lua_tostring(lua.state, pos);
	return (*this);
}

const char* LuaStack::cstring(int pos)
{
	checkPos(pos);
	return lua_tostring(lua.state, pos);
}

std::string LuaStack::string(int pos)
{
	checkPos(pos);
	return std::string(cstring(pos));
}

LuaStack& LuaStack::to(bool& sink, int pos)
{
	checkPos(pos);
	sink = lua_toboolean(lua.state, pos);
	return (*this);
}

bool LuaStack::boolean(int pos)
{
	bool b;
	to(b, pos);
	return b;
}

LuaStack& LuaStack::to(lua_Number& sink, int pos)
{
	checkPos(pos);
	sink = lua_tonumber(lua.state, pos);
	return (*this);
}

LuaStack& LuaStack::to(int&sink, int pos)
{
	checkPos(pos);
	sink = lua_tointeger(lua.state, pos);
	return (*this);
}

double LuaStack::number(int pos)
{
	double b;
	to(b, pos);
	return b;
}

LuaStack& LuaStack::global(const char* name)
{
	lua_getglobal(lua.state, name);
	return (*this);
}

LuaStack& LuaStack::global(const std::string& name)
{
	global(name.c_str());
	return (*this);
}

LuaStack& LuaStack::set(const char* key, int tablePos)
{
	checkPos(tablePos);
	lua_setfield(lua.state, tablePos, key);
	return (*this);
}

LuaStack& LuaStack::set(const std::string& key, int tablePos)
{
	return set(key.c_str(), tablePos);
}

LuaStack& LuaStack::push(const char* value)
{
	lua_pushstring(lua.state, value);
	return (*this);
}

LuaStack& LuaStack::push(const std::string& value)
{
	return push(value.c_str());
}

LuaStack& LuaStack::push(const lua_Number& value)
{
	lua_pushnumber(lua.state, value);
	return (*this);
}

LuaStack& LuaStack::push(const int& value)
{
	lua_pushnumber(lua.state, value);
	return (*this);
}

LuaStack& LuaStack::push(void* const p)
{
	lua_pushlightuserdata(lua.state, p);
	return (*this);
}

LuaStack& LuaStack::push(const bool& b)
{
	lua_pushboolean(lua.state, b);
	return (*this);
}

LuaStack& LuaStack::push(void(*p)(Lua& lua, LuaStack& stack))
{
	return this->push(LuaCallable(p));
}

LuaStack& LuaStack::push(const LuaCallable& f)
{
	// XXX This definitely, definitely leaks.
	lua_pushlightuserdata(lua.state, new ForwardingLuaFunction(lua, f));
	lua_pushcclosure(lua.state, invokeWrappedFunction, 1);
	return (*this);
}

LuaStack::~LuaStack()
{
	if (size() > 0)
		lua_pop(lua.state, size());
}

void LuaStack::ForwardingLuaFunction::operator ()()
{
	LuaStack stack(lua);
	stack.offset(0);
	f(lua, stack);
	stack.offset(stack.size());
}