#ifndef LUACXX_QOBJECTSLOT_INCLUDED
#define LUACXX_QOBJECTSLOT_INCLUDED

#include "Qt5Core.hpp"
#include "reference.hpp"

#include <QObject>
#include <QMetaObject>
#include <QMetaMethod>

#include <memory>
#include <unordered_set>

namespace lua {

class QObjectSlot : public QObject
{
    QMetaMethod _signal;
    lua::reference _slot;
public:
    QObjectSlot(QObject* const parent, const QMetaMethod& signal, const lua::index& slot);

    int qt_metacall(QMetaObject::Call call, int id, void **arguments);

    virtual ~QObjectSlot();

    static void disconnect(QObjectSlot* const slot);
    static void connect(QObjectSlot* const slot);
};

} // namespace lua

#endif // LUACXX_QOBJECTSLOT_INCLUDED
