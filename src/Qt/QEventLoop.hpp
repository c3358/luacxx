#ifndef LUACXX_QEVENTLOOP_INCLUDED
#define LUACXX_QEVENTLOOP_INCLUDED

#include "../luacxx/stack.hpp"

class QEventLoop;

namespace lua {

void QEventLoop_metatable(const lua::index& mt);

template <>
struct Metatable<QEventLoop>
{
    static constexpr const char* name = "QEventLoop";

    static bool metatable(const lua::index& mt, QEventLoop* const)
    {
        lua::QEventLoop_metatable(mt);
        return true;
    }
};

}; // namespace lua

extern "C" int luaopen_luacxx_QEventLoop(lua_State* const);

#endif // LUACXX_QEVENTLOOP_INCLUDED
