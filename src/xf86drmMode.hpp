/*


xf86drmMode.h uses the following license:

 * Copyright (c) 2007-2008 Tungsten Graphics, Inc., Cedar Park, Texas.
 * Copyright (c) 2007-2008 Dave Airlie <airlied@linux.ie>
 * Copyright (c) 2007-2008 Jakob Bornecrantz <wallbraker@gmail.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.

*/

#include "stack.hpp"

#include "convert/char.hpp"

#include <drm/drm_mode.h>
#include <xf86drmMode.h>

LUA_METATABLE_NAMED(drm_clip_rect);
LUA_METATABLE_NAMED(_drmModeConnector);
LUA_METATABLE_NAMED(drmModeConnection);
LUA_METATABLE_NAMED(_drmModeEncoder);
LUA_METATABLE_NAMED(_drmModeObjectProperties);
LUA_METATABLE_NAMED(_drmModePlane);
LUA_METATABLE_NAMED(_drmModeProperty);
LUA_METATABLE_NAMED(_drmModePropertyBlob);
LUA_METATABLE_NAMED(_drmModePlaneRes);
LUA_METATABLE_NAMED(drmModeSubPixel);
LUA_METATABLE_NAMED(_drmModeModeInfo);
LUA_METATABLE_NAMED(_drmModeRes);
LUA_METATABLE_NAMED(_drmModeFB);
LUA_METATABLE_NAMED(_drmModeCrtc);

extern "C" int luaopen_xf86drmMode(lua_State* const state);
