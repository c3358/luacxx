#include "QOpenGLContextGroup.hpp"
#include "../luacxx/type/function.hpp"
#include "../luacxx/thread.hpp"

#include <QOpenGLContextGroup>

void lua::QOpenGLContextGroup_metatable(const lua::index& mt)
{
    mt["shares"] = &QOpenGLContextGroup::shares;
}

int luaopen_luacxx_QOpenGLContextGroup(lua_State* const state)
{
    lua::thread env(state);

    env["QOpenGLContextGroup"] = lua::value::table;
    env["QOpenGLContextGroup"]["currentContextGroup"] = &QOpenGLContextGroup::currentContextGroup;

    return 0;
}
