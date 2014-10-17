#include "QMatrix.hpp"
#include "../convert/callable.hpp"
#include "../thread.hpp"

#include <QMatrix>

void lua::QMatrix_metatable(lua_State* const state, const int pos)
{
    // TODO Set up metatable methods for this class
}

int QMatrix_new(lua_State* const state)
{
    lua::make<QMatrix>(state);
    // TODO Set up object-specific methods

    return 1;
}

int luaopen_Qt5Gui_QMatrix(lua_State* const state)
{
    lua::thread env(state);

    env["QMatrix"] = lua::value::table;
    env["QMatrix"]["new"] = QMatrix_new;

    return 0;
}
