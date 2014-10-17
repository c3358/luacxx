#include "QGradient.hpp"
#include "../convert/callable.hpp"
#include "../thread.hpp"

#include <QGradient>

void lua::QGradient_metatable(lua_State* const state, const int pos)
{
    lua::index mt(state, pos);
    mt["coordinateMode"] = &QGradient::coordinateMode ;
    mt["setColorAt"] = &QGradient::setColorAt ;
    mt["setCoordinateMode"] = &QGradient::setCoordinateMode ;
    mt["setSpread"] = &QGradient::setSpread ;
    mt["setStops"] = &QGradient::setStops ;
    mt["spread"] = &QGradient::spread ;
    mt["stops"] = &QGradient::stops ;
    mt["type"] = &QGradient::type ;
}

int luaopen_Qt5Gui_QGradient(lua_State* const state)
{
    lua::thread env(state);

    env["QGradient"] = lua::value::table;

    // enum QGradient::CoordinateMode
    env["QGradient"]["LogicalMode"] = QGradient::LogicalMode;
    env["QGradient"]["StretchToDeviceMode"] = QGradient::StretchToDeviceMode;
    env["QGradient"]["ObjectBoundingMode"] = QGradient::ObjectBoundingMode;

    // enum QGradient::Spread
    env["QGradient"]["PadSpread"] = QGradient::PadSpread;
    env["QGradient"]["RepeatSpread"] = QGradient::RepeatSpread;
    env["QGradient"]["ReflectSpread"] = QGradient::ReflectSpread;

    // enum QGradient::Type
    env["QGradient"]["LinearGradient"] = QGradient::LinearGradient;
    env["QGradient"]["RadialGradient"] = QGradient::RadialGradient;
    env["QGradient"]["ConicalGradient"] = QGradient::ConicalGradient;
    env["QGradient"]["NoGradient"] = QGradient::NoGradient;

    return 0;
}
