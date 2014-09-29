#ifndef LUACXX_QICON_INCLUDED
#define LUACXX_QICON_INCLUDED

#include "Qt5Gui.hpp"
#include <QIcon>

namespace lua {

void QIcon_metatable(const lua::index& mt);

template <>
struct Metatable<QIcon>
{
    static constexpr const char* name = "QIcon";

    static bool metatable(const lua::index& mt, QIcon* const)
    {
        lua::QIcon_metatable(mt);
        return true;
    }
};

}; // namespace lua

extern "C" int luaopen_Qt5Gui_QIcon(lua_State* const);

#endif // LUACXX_QICON_INCLUDED
