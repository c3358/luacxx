#include "numeric.hpp"
#include "../algorithm.hpp"

#include "const_char_p.hpp"

void lua::store_lua_Integer(long& destination, lua_State* const state, const int source_pos)
{
    lua::index source(state, source_pos);

    if (source.type().number()) {
        destination = lua_tointeger(source.state(), source.pos());
        return;
    }
    if (source.type().string()) {
        destination = source.get<const char*>()[0];
        return;
    }
    if (source.type().userdata()) {
        switch (lua::object_size(state, source_pos)) {
            case sizeof(int):
                destination = *static_cast<char*>(lua::get<void*>(source));
                return;
            case sizeof(long):
                destination = *static_cast<long*>(lua::get<void*>(source));
                return;
            case sizeof(short):
                destination = *static_cast<short*>(lua::get<void*>(source));
                return;
            case sizeof(char):
                destination = *static_cast<char*>(lua::get<void*>(source));
                return;
        }
    }
    destination = 0;
}

void lua::store_lua_Unsigned(lua_Unsigned& destination, lua_State* const state, const int source_pos)
{
    lua::index source(state, source_pos);

    if (source.type().number()) {
        destination = lua_tounsigned(source.state(), source.pos());
        return;
    }
    if (source.type().string()) {
        destination = source.get<const char*>()[0];
        return;
    }
    if (source.type().userdata()) {
        switch (lua::object_size(state, source_pos)) {
            case sizeof(unsigned int):
                destination = *static_cast<unsigned char*>(lua::get<void*>(source));
                return;
            case sizeof(unsigned long):
                destination = *static_cast<unsigned long*>(lua::get<void*>(source));
                return;
            case sizeof(unsigned short):
                destination = *static_cast<unsigned short*>(lua::get<void*>(source));
                return;
            case sizeof(unsigned char):
                destination = *static_cast<unsigned char*>(lua::get<void*>(source));
                return;
        }
    }
    destination = 0;
}
