#include "QSurfaceFormat.hpp"

#include "../convert/callable.hpp"
#include "../thread.hpp"

int QSurfaceFormat_setOption(lua_State* const state)
{
    auto self = lua::get<QSurfaceFormat*>(state, 1);
    #if QT_VERSION >= QT_VERSION_CHECK(5, 3, 0)
    if (lua_gettop(state) > 2) {
        self->setOption(
            lua::get<QSurfaceFormat::FormatOption>(state, 2),
            lua::get<bool>(state, 3)
        );
    } else {
        self->setOption(
            lua::get<QSurfaceFormat::FormatOption>(state, 2)
        );
    }
    #else
    self->setOption(
        lua::get<QSurfaceFormat::FormatOptions>(state, 2)
    );
    #endif
    return 0;
}

int QSurfaceFormat_testOption(lua_State* const state)
{
    auto self = lua::get<QSurfaceFormat*>(state, 1);
    #if QT_VERSION >= QT_VERSION_CHECK(5, 3, 0)
    lua::push(state, self->testOption(
        lua::get<QSurfaceFormat::FormatOption>(state, 2)
    ));
    #else
    lua::push(state, self->testOption(
        lua::get<QSurfaceFormat::FormatOptions>(state, 2)
    ));
    #endif
    return 1;
}

void lua::QSurfaceFormat_metatable(lua_State* const state, const int pos)
{
    lua::index mt(state, pos);
    mt["alphaBufferSize"] = &QSurfaceFormat::alphaBufferSize;
    mt["blueBufferSize"] = &QSurfaceFormat::blueBufferSize;
    mt["depthBufferSize"] = &QSurfaceFormat::depthBufferSize;
    mt["greenBufferSize"] = &QSurfaceFormat::greenBufferSize;
    mt["hasAlpha"] = &QSurfaceFormat::hasAlpha;
    mt["majorVersion"] = &QSurfaceFormat::majorVersion;
    mt["minorVersion"] = &QSurfaceFormat::minorVersion;
    mt["profile"] = &QSurfaceFormat::profile;
    mt["redBufferSize"] = &QSurfaceFormat::redBufferSize;
    mt["renderableType"] = &QSurfaceFormat::renderableType;
    mt["samples"] = &QSurfaceFormat::samples;
    mt["setAlphaBufferSize"] = &QSurfaceFormat::setAlphaBufferSize;
    mt["setBlueBufferSize"] = &QSurfaceFormat::setBlueBufferSize;
    mt["setDepthBufferSize"] = &QSurfaceFormat::setDepthBufferSize;
    mt["setGreenBufferSize"] = &QSurfaceFormat::setGreenBufferSize;
    mt["setMajorVersion"] = &QSurfaceFormat::setMajorVersion;
    mt["setMinorVersion"] = &QSurfaceFormat::setMinorVersion;
    mt["setOption"] = QSurfaceFormat_setOption;
    mt["setProfile"] = &QSurfaceFormat::setProfile;
    mt["setRedBufferSize"] = &QSurfaceFormat::setRedBufferSize;
    mt["setRenderableType"] = &QSurfaceFormat::setRenderableType;
    mt["setSamples"] = &QSurfaceFormat::setSamples;
    mt["setStencilBufferSize"] = &QSurfaceFormat::setStencilBufferSize;
    mt["setStereo"] = &QSurfaceFormat::setStereo;
    mt["setSwapBehavior"] = &QSurfaceFormat::setSwapBehavior;
    mt["setVersion"] = &QSurfaceFormat::setVersion;
    mt["stencilBufferSize"] = &QSurfaceFormat::stencilBufferSize;
    mt["stereo"] = &QSurfaceFormat::stereo;
    mt["swapBehavior"] = &QSurfaceFormat::swapBehavior;
    mt["testOption"] = QSurfaceFormat_testOption;
    mt["version"] = &QSurfaceFormat::version;

    #if QT_VERSION >= QT_VERSION_CHECK(5, 3, 0)
    mt["options"] = &QSurfaceFormat::options;
    mt["setOptions"] = &QSurfaceFormat::setOptions;

    mt["swapInterval"] = &QSurfaceFormat::swapInterval;
    mt["setSwapInterval"] = &QSurfaceFormat::setSwapInterval;
    #endif
}

/*

QSurfaceFormat()
QSurfaceFormat(FormatOptions options)
QSurfaceFormat(const QSurfaceFormat & other)

*/
int QSurfaceFormat_new(lua_State* const state)
{
    if (lua_gettop(state) < 2) {
        lua::make<QSurfaceFormat>(state);
        return 1;
    }
    if (lua::is_type<QSurfaceFormat>(state, 2)) {
        lua::make<QSurfaceFormat>(state, lua::get<const QSurfaceFormat&>(state, 2));
        return 1;
    }

    lua::make<QSurfaceFormat>(state,
        lua::get<QSurfaceFormat::FormatOptions>(state, 2)
    );
    return 1;
}

int luaopen_Qt5Gui_QSurfaceFormat(lua_State* const state)
{
    lua::thread env(state);

    env["QSurfaceFormat"] = lua::value::table;
    env["QSurfaceFormat"]["new"] = QSurfaceFormat_new;
    auto t = env["QSurfaceFormat"];

    // enum QSurfaceFormat::FormatOption
    // flags QSurfaceFormat::FormatOptions
    t["StereoBuffers"] = QSurfaceFormat::StereoBuffers;
    t["DebugContext"] = QSurfaceFormat::DebugContext;
    t["DeprecatedFunctions"] = QSurfaceFormat::DeprecatedFunctions;

    // enum QSurfaceFormat::OpenGLContextProfile
    t["NoProfile"] = QSurfaceFormat::NoProfile;
    t["CoreProfile"] = QSurfaceFormat::CoreProfile;
    t["CompatibilityProfile"] = QSurfaceFormat::CompatibilityProfile;

    // enum QSurfaceFormat::RenderableType
    t["DefaultRenderableType"] = QSurfaceFormat::DefaultRenderableType;
    t["OpenGL"] = QSurfaceFormat::OpenGL;
    t["OpenGLES"] = QSurfaceFormat::OpenGLES;
    t["OpenVG"] = QSurfaceFormat::OpenVG;

    // enum QSurfaceFormat::SwapBehavior
    t["DefaultSwapBehavior"] = QSurfaceFormat::DefaultSwapBehavior;
    t["SingleBuffer"] = QSurfaceFormat::SingleBuffer;
    t["DoubleBuffer"] = QSurfaceFormat::DoubleBuffer;
    t["TripleBuffer"] = QSurfaceFormat::TripleBuffer;

    return 0;
}
