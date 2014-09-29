#ifndef LUACXX_tests_Qt5Gui_INCLUDED
#define LUACXX_tests_Qt5Gui_INCLUDED

#include "Qt5Core/QObject.hpp"

#include <QObject>
#include <QPoint>

class QtPoint : public QObject
{
    Q_OBJECT

    int _x;
    int _y;

    Q_PROPERTY(int x READ getX WRITE setX)
    Q_PROPERTY(int y READ getY WRITE setY)
public:

    QtPoint() :
        _x(),
        _y()
    {
    }

    QtPoint(const int x, const int y) :
        _x(x),
        _y(y)
    {
    }

    Q_INVOKABLE void setX(const int x)
    {
        _x = x;
        emit xChanged();
    }

    Q_INVOKABLE const int getX() const
    {
        return _x;
    }

    Q_INVOKABLE void setY(const int y)
    {
        _y = y;
        emit yChanged();
    }

    Q_INVOKABLE const int getY() const
    {
        return _y;
    }

signals:
    void xChanged() const;
    void yChanged() const;
};

namespace lua {

template <>
struct Metatable<QtPoint>
{
    static constexpr const char* name = "QtPoint";

    static bool metatable(const lua::index& mt, const QtPoint* const)
    {
        lua::QObject_metatable(mt);
        return true;
    }
};

}; // namespace lua

#endif // LUACXX_tests_Qt5Gui_INCLUDED
