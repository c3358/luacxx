#ifndef LUACXX_QSET_INCLUDED
#define LUACXX_QSET_INCLUDED

#include "../luacxx/stack.hpp"
/*

class QSet;

namespace lua {

void QSet_metatable(const lua::index& mt);

template <>
struct Metatable<QSet>
{
    static constexpr const char* name = "QSet";

    static bool metatable(const lua::index& mt, QSet* const)
    {
        lua::QSet_metatable(mt);
        return true;
    }
};

}; // namespace lua

extern "C" int luaopen_luacxx_QSet(lua_State* const);
*/

#endif // LUACXX_QSET_INCLUDED
