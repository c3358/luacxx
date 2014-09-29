#ifndef LUACXX_QTRANSFORM_INCLUDED
#define LUACXX_QTRANSFORM_INCLUDED

#include "Qt5Gui.hpp"

class QTransform;

namespace lua {

void QTransform_metatable(const lua::index& mt);

template <>
struct Metatable<QTransform>
{
    static constexpr const char* name = "QTransform";

    static bool metatable(const lua::index& mt, QTransform* const)
    {
        lua::QTransform_metatable(mt);
        return true;
    }
};

}; // namespace lua

extern "C" int luaopen_Qt5Gui_QTransform(lua_State* const);

#endif // LUACXX_QTRANSFORM_INCLUDED
