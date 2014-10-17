#include "QVector4D.hpp"
#include "../convert/callable.hpp"
#include "../thread.hpp"

#include <QVector4D>

void lua::QVector4D_metatable(lua_State* const state, const int pos)
{
    // TODO Set up metatable methods for this class
}

int QVector4D_new(lua_State* const state)
{
    lua::make<QVector4D>(state);
    // TODO Set up object-specific methods

    return 1;
}

int luaopen_Qt5Gui_QVector4D(lua_State* const state)
{
    lua::thread env(state);

    env["QVector4D"] = lua::value::table;
    env["QVector4D"]["new"] = QVector4D_new;

    return 0;
}
