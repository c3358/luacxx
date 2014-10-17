#include "QGlyphRun.hpp"
#include "../convert/callable.hpp"
#include "../thread.hpp"
#include "../Qt5Core/QRectF.hpp"
#include "../Qt5Core/QVector.hpp"

#include <QRectF>
#include <QGlyphRun>

void lua::QGlyphRun_metatable(lua_State* const state, const int pos)
{
    lua::index mt(state, pos);
    mt["boundingRect"] = &QGlyphRun::boundingRect;
    mt["clear"] = &QGlyphRun::clear;
    mt["flags"] = &QGlyphRun::flags;
    mt["glyphIndexes"] = &QGlyphRun::glyphIndexes;
    mt["isEmpty"] = &QGlyphRun::isEmpty;
    mt["isRightToLeft"] = &QGlyphRun::isRightToLeft;
    mt["overline"] = &QGlyphRun::overline;
    mt["positions"] = &QGlyphRun::positions;
    mt["rawFont"] = &QGlyphRun::rawFont;
    mt["setBoundingRect"] = &QGlyphRun::setBoundingRect;
    mt["setFlag"] = &QGlyphRun::setFlag;
    mt["setFlags"] = &QGlyphRun::setFlags;
    mt["setGlyphIndexes"] = &QGlyphRun::setGlyphIndexes;
    mt["setOverline"] = &QGlyphRun::setOverline;
    mt["setPositions"] = &QGlyphRun::setPositions;
    mt["setRawData"] = &QGlyphRun::setRawData;
    mt["setRawFont"] = &QGlyphRun::setRawFont;
    mt["setRightToLeft"] = &QGlyphRun::setRightToLeft;
    mt["setStrikeOut"] = &QGlyphRun::setStrikeOut;
    mt["setUnderline"] = &QGlyphRun::setUnderline;
    mt["strikeOut"] = &QGlyphRun::strikeOut;
    mt["swap"] = &QGlyphRun::swap;
    mt["underline"] = &QGlyphRun::underline;
}

int QGlyphRun_new(lua_State* const state)
{
    if (lua_gettop(state) > 1) {
        lua::make<QGlyphRun>(state, lua::get<const QGlyphRun&>(state, 2));
    } else {
        lua::make<QGlyphRun>(state);
    }

    return 1;
}

int luaopen_Qt5Gui_QGlyphRun(lua_State* const state)
{
    lua::thread env(state);

    env["QGlyphRun"] = lua::value::table;
    env["QGlyphRun"]["new"] = QGlyphRun_new;

    env["QGlyphRun"]["Overline"] = QGlyphRun::Overline;
    env["QGlyphRun"]["Underline"] = QGlyphRun::Underline;
    env["QGlyphRun"]["StrikeOut"] = QGlyphRun::StrikeOut;
    env["QGlyphRun"]["RightToLeft"] = QGlyphRun::RightToLeft;
    env["QGlyphRun"]["SplitLigature"] = QGlyphRun::SplitLigature;

    return 0;
}
