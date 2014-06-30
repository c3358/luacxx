#ifndef LUACXX_QIMAGE_INCLUDED
#define LUACXX_QIMAGE_INCLUDED

#include "../luacxx/stack.hpp"

class QImage;

namespace lua {

void QImage_metatable(const lua::index& mt);

template <>
struct Metatable<QImage>
{
    static constexpr const char* name = "QImage";

    static bool metatable(const lua::index& mt, QImage* const)
    {
        lua::QImage_metatable(mt);
        return true;
    }
};

}; // namespace lua

extern "C" int luaopen_luacxx_QImage(lua_State* const);

#endif // LUACXX_QIMAGE_INCLUDED
