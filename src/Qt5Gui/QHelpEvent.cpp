#include "QHelpEvent.hpp"
#include "../convert/callable.hpp"
#include "../thread.hpp"

#include "../Qt5Core/QPoint.hpp"
#include "../Qt5Core/QEvent.hpp"

namespace lua {

void QHelpEvent_metatable(lua_State* const state, const int pos)
{
    lua::QEvent_metatable(state, pos);

    lua::index mt(state, pos);
    mt["globalPos"] = &QHelpEvent::globalPos;
    mt["globalX"] = &QHelpEvent::globalX;
    mt["globalY"] = &QHelpEvent::globalY;
    mt["pos"] = &QHelpEvent::pos;
    mt["x"] = &QHelpEvent::x;
    mt["y"] = &QHelpEvent::y;
}

} // namespace lua

int QHelpEvent_new(lua_State* const state)
{
    lua::make<QHelpEvent>(state,
        lua::get<QEvent::Type>(state, 1),
        lua::get<const QPoint&>(state, 2),
        lua::get<const QPoint&>(state, 3)
    );

    return 1;
}

QHelpEvent* QHelpEvent_cast(QEvent* event)
{
    switch (event->type()) {
    case QEvent::GraphicsSceneHelp:
    case QEvent::ToolTip:
    case QEvent::WhatsThis:
        return static_cast<QHelpEvent*>(event);
    default:
        return nullptr;
    }
}

int luaopen_Qt5Gui_QHelpEvent(lua_State* const state)
{
    lua::thread env(state);

    env["QHelpEvent"] = lua::value::table;
    env["QHelpEvent"]["new"] = QHelpEvent_new;
    auto t = env["QHelpEvent"];

    t["cast"] = QHelpEvent_cast;

    return 0;
}
