#include "QVector3D.hpp"
#include "../convert/callable.hpp"
#include "../convert/numeric.hpp"
#include "../thread.hpp"

#include "QVector2D.hpp"
#include "../Qt5Core/QPointF.hpp"
#include "../Qt5Core/QPoint.hpp"
#include <QVector3D>

void lua::QVector3D_metatable(lua_State* const state, const int pos)
{
    lua::index mt(state, pos);
    mt["distanceToLine"] = &QVector3D::distanceToLine;
    //mt["distanceToPlane"] = &QVector3D::distanceToPlane;
    mt["isNull"] = &QVector3D::isNull;
    mt["length"] = &QVector3D::length;
    mt["lengthSquared"] = &QVector3D::lengthSquared;
    mt["normalize"] = &QVector3D::normalize;
    mt["normalized"] = &QVector3D::normalized;
    mt["setX"] = &QVector3D::setX;
    mt["setY"] = &QVector3D::setY;
    mt["setZ"] = &QVector3D::setZ;
    mt["toPoint"] = &QVector3D::toPoint;
    mt["toPointF"] = &QVector3D::toPointF;
    //mt["toVector2D"] = &QVector3D::toVector2D;
    //mt["toVector4D"] = &QVector3D::toVector4D;
    mt["x"] = &QVector3D::x;
    mt["y"] = &QVector3D::y;
    mt["z"] = &QVector3D::z;
}


int QVector3D_new(lua_State* const state)
{
    switch (lua_gettop(state)) {
    case 1:
        // QVector3D ()
        lua::make<QVector3D>(state);
        break;
    case 2:
    {
        // TODO
        // QVector3D ( const QVector4D & vector )
        // QVector3D ( const QPoint & point )
        // QVector3D ( const QPointF & point )
        // QVector3D ( const QVector2D & vector )
        lua::make<QVector3D>(state);
        break;
    }
    case 3:
        // QVector3D ( const QVector2D & vector, qreal zpos )
        lua::make<QVector3D>(state,
            lua::get<const QVector2D&>(state, 2),
            lua::get<qreal>(state, 3)
        );
        break;
    default:
        // QVector3D ( qreal xpos, qreal ypos, qreal zpos )
        lua::make<QVector3D>(state,
            lua::get<qreal>(state, 2),
            lua::get<qreal>(state, 3),
            lua::get<qreal>(state, 4)
        );
        break;
    }

    return 1;
}

int luaopen_Qt5Gui_QVector3D(lua_State* const state)
{
    lua::thread env(state);

    env["QVector3D"] = lua::value::table;
    env["QVector3D"]["new"] = QVector3D_new;

    return 0;
}
