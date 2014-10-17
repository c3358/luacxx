#include "QCursor.hpp"
#include "../convert/callable.hpp"
#include "../thread.hpp"
#include "../Qt5Core/QPoint.hpp"
#include "QPixmap.hpp"
#include "QBitmap.hpp"

#include <QCursor>

// http://qt-project.org/doc/qt-4.8/qcursor.html

void lua::QCursor_metatable(lua_State* const state, const int pos)
{
    lua::index mt(state, pos);
    mt["bitmap"] = &QCursor::bitmap;
    mt["hotSpot"] = &QCursor::hotSpot;
    mt["mask"] = &QCursor::mask;
    mt["pixmap"] = &QCursor::pixmap;
    mt["setShape"] = &QCursor::setShape;
    mt["shape"] = &QCursor::shape;
}

/*
    QCursor ()
    QCursor ( Qt::CursorShape shape )
    QCursor ( const QBitmap & bitmap, const QBitmap & mask, int hotX = -1, int hotY = -1 )
    QCursor ( const QPixmap & pixmap, int hotX = -1, int hotY = -1 )
    QCursor ( const QCursor & c )
    QCursor ( HCURSOR cursor )
    QCursor ( Qt::HANDLE handle )
*/
int QCursor_new(lua_State* const state)
{
    lua::make<QCursor>(state);
    // TODO Set up object-specific methods

    return 1;
}

/*
    QPoint  pos ()
    void    setPos ( int x, int y )
    void    setPos ( const QPoint & p )
*/
int luaopen_Qt5Gui_QCursor(lua_State* const state)
{
    lua::thread env(state);

    env["QCursor"] = lua::value::table;
    env["QCursor"]["new"] = QCursor_new;

    return 0;
}
