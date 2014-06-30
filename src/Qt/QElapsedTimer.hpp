#ifndef LUACXX_QELAPSEDTIMER_INCLUDED
#define LUACXX_QELAPSEDTIMER_INCLUDED

#include "../luacxx/stack.hpp"

class QElapsedTimer;

namespace lua {

void QElapsedTimer_metatable(const lua::index& mt);

template <>
struct Metatable<QElapsedTimer>
{
    static constexpr const char* name = "QElapsedTimer";

    static bool metatable(const lua::index& mt, QElapsedTimer* const)
    {
        lua::QElapsedTimer_metatable(mt);
        return true;
    }
};

}; // namespace lua

extern "C" int luaopen_luacxx_QElapsedTimer(lua_State* const);

#endif // LUACXX_QELAPSEDTIMER_INCLUDED
