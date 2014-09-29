#ifndef LUACXX_QGLYPHRUN_INCLUDED
#define LUACXX_QGLYPHRUN_INCLUDED

#include "Qt5Gui.hpp"

class QGlyphRun;

namespace lua {

void QGlyphRun_metatable(const lua::index& mt);

template <>
struct Metatable<QGlyphRun>
{
    static constexpr const char* name = "QGlyphRun";

    static bool metatable(const lua::index& mt, QGlyphRun* const)
    {
        lua::QGlyphRun_metatable(mt);
        return true;
    }
};

}; // namespace lua

extern "C" int luaopen_Qt5Gui_QGlyphRun(lua_State* const);

#endif // LUACXX_QGLYPHRUN_INCLUDED
