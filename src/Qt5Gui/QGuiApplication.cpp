#include "QGuiApplication.hpp"
#include "../Qt5Core/QCoreApplication.hpp"
#include "../Qt5Core/QObject.hpp"
#include "../Qt5Core/QEventLoop.hpp"

#include "../convert/callable.hpp"
#include "../convert/numeric.hpp"
#include "../thread.hpp"
#include "QClipboard.hpp"
#include "../Qt5Core/QObject.hpp"
#include "QPalette.hpp"
#include "QScreen.hpp"
#include "QCursor.hpp"
#include "QFont.hpp"
#include "QInputMethod.hpp"
#include "../Qt5Core/QList.hpp"
#include "../Qt5Core/Qt.hpp"
#include "../Qt5Core/QPoint.hpp"
#include "QIcon.hpp"
#include "QWindow.hpp"
#include "../Qt5Core/QFlags.hpp"

void lua::QStyleHints_metatable(lua_State* const state, const int pos)
{

}

void lua::QGuiApplication_metatable(lua_State* const state, const int pos)
{
    lua::QCoreApplication_metatable(state, pos);

    lua::index mt(state, pos);
    mt["devicePixelRatio"] = &QGuiApplication::devicePixelRatio;
    mt["isSavingSession"] = &QGuiApplication::isSavingSession;
    mt["isSessionRestored"] = &QGuiApplication::isSessionRestored;
    mt["sessionId"] = &QGuiApplication::sessionId;
    mt["sessionKey"] = &QGuiApplication::sessionKey;
}

int QGuiApplication_platformNativeInterface(lua_State* const state)
{
    lua::push<void*>(state, QGuiApplication::platformNativeInterface());
    return 1;
}

int luaopen_Qt5Gui_QGuiApplication(lua_State* const state)
{
    luaL_requiref(state, "Qt5Gui.QEventLoop", luaopen_Qt5Core_QEventLoop, false);
    lua_settop(state, 0);

    lua::thread env(state);

    env["QGuiApplication"] = lua::value::table;
    env["QGuiApplication"]["new"] = lua::QCoreApplication_new<QGuiApplication>;
    auto t = env["QGuiApplication"];

    t["allWindows"] = &QGuiApplication::allWindows;
    t["applicationDisplayName"] = &QGuiApplication::applicationDisplayName;
    t["applicationState"] = &QGuiApplication::applicationState;
    t["changeOverrideCursor"] = &QGuiApplication::changeOverrideCursor;
    t["clipboard"] = &QGuiApplication::clipboard;
    t["desktopSettingsAware"] = &QGuiApplication::desktopSettingsAware;
    t["exec"] = &QGuiApplication::exec;
    t["focusObject"] = &QGuiApplication::focusObject;
    t["focusWindow"] = &QGuiApplication::focusWindow;
    t["font"] = &QGuiApplication::font;
    t["inputMethod"] = &QGuiApplication::inputMethod;
    t["isLeftToRight"] = &QGuiApplication::isLeftToRight;
    t["isRightToLeft"] = &QGuiApplication::isRightToLeft;
    t["keyboardModifiers"] = &QGuiApplication::keyboardModifiers;
    t["layoutDirection"] = &QGuiApplication::layoutDirection;
    t["modalWindow"] = &QGuiApplication::modalWindow;
    t["mouseButtons"] = &QGuiApplication::mouseButtons;
    t["overrideCursor"] = &QGuiApplication::overrideCursor;
    t["palette"] = &QGuiApplication::palette;
    t["platformName"] = &QGuiApplication::platformName;
    t["platformNativeInterface"] = &QGuiApplication_platformNativeInterface;
    t["primaryScreen"] = &QGuiApplication::primaryScreen;
    t["queryKeyboardModifiers"] = &QGuiApplication::queryKeyboardModifiers;
    t["quitOnLastWindowClosed"] = &QGuiApplication::quitOnLastWindowClosed;
    t["restoreOverrideCursor"] = &QGuiApplication::restoreOverrideCursor;
    t["screens"] = &QGuiApplication::screens;
    t["setApplicationDisplayName"] = &QGuiApplication::setApplicationDisplayName;
    t["setDesktopSettingsAware"] = &QGuiApplication::setDesktopSettingsAware;
    t["setFont"] = &QGuiApplication::setFont;
    t["setLayoutDirection"] = &QGuiApplication::setLayoutDirection;
    t["setOverrideCursor"] = &QGuiApplication::setOverrideCursor;
    t["setPalette"] = &QGuiApplication::setPalette;
    t["setQuitOnLastWindowClosed"] = &QGuiApplication::setQuitOnLastWindowClosed;
    t["styleHints"] = &QGuiApplication::styleHints;
    t["sync"] = &QGuiApplication::sync;
    t["topLevelAt"] = &QGuiApplication::topLevelAt;
    t["topLevelWindows"] = &QGuiApplication::topLevelWindows;

    #if QT_VERSION >= QT_VERSION_CHECK(5, 3, 0)
    t["setWindowIcon"] = &QGuiApplication::setWindowIcon;
    t["windowIcon"] = &QGuiApplication::windowIcon;
    #endif

    return 0;
}
