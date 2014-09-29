#include "QImageReader.hpp"
#include "../type/function.hpp"
#include "../thread.hpp"

#include <QImageReader>

#include "QColor.hpp"
#include "../Qt5Core/QRect.hpp"
#include "../Qt5Core/QIODevice.hpp"
#include "../Qt5Core/QString.hpp"
#include "QImage.hpp"
#include "../Qt5Core/QSize.hpp"
#include "../Qt5Core/QByteArray.hpp"
#include "QImageIOHandler.hpp"
#include "../Qt5Core/QList.hpp"

// https://qt-project.org/doc/qt-5/qimagereader.html

void lua::QImageReader_metatable(const lua::index& mt)
{
    mt["autoDetectImageFormat"] = &QImageReader::autoDetectImageFormat;
    mt["backgroundColor"] = &QImageReader::backgroundColor;
    mt["canRead"] = &QImageReader::canRead;
    mt["clipRect"] = &QImageReader::clipRect;
    mt["currentImageNumber"] = &QImageReader::currentImageNumber;
    mt["currentImageRect"] = &QImageReader::currentImageRect;
    mt["decideFormatFromContent"] = &QImageReader::decideFormatFromContent;
    mt["device"] = &QImageReader::device;
    mt["error"] = &QImageReader::error;
    mt["errorString"] = &QImageReader::errorString;
    mt["fileName"] = &QImageReader::fileName;
    mt["format"] = &QImageReader::format;
    mt["imageCount"] = &QImageReader::imageCount;
    mt["imageFormat"] = &QImageReader::imageFormat;
    mt["jumpToImage"] = &QImageReader::jumpToImage;
    mt["jumpToNextImage"] = &QImageReader::jumpToNextImage;
    mt["loopCount"] = &QImageReader::loopCount;
    mt["nextImageDelay"] = &QImageReader::nextImageDelay;
    mt["quality"] = &QImageReader::quality;
    mt["read"] = QImageReader_read;
    mt["scaledClipRect"] = &QImageReader::scaledClipRect;
    mt["scaledSize"] = &QImageReader::scaledSize;
    mt["setAutoDetectImageFormat"] = &QImageReader::setAutoDetectImageFormat;
    mt["setBackgroundColor"] = &QImageReader::setBackgroundColor;
    mt["setClipRect"] = &QImageReader::setClipRect;
    mt["setDecideFormatFromContent"] = &QImageReader::setDecideFormatFromContent;
    mt["setDevice"] = &QImageReader::setDevice;
    mt["setFileName"] = &QImageReader::setFileName;
    mt["setFormat"] = &QImageReader::setFormat;
    mt["setQuality"] = &QImageReader::setQuality;
    mt["setScaledClipRect"] = &QImageReader::setScaledClipRect;
    mt["setScaledSize"] = &QImageReader::setScaledSize;
    mt["size"] = &QImageReader::size;
    mt["supportsAnimation"] = &QImageReader::supportsAnimation;
    mt["supportsOption"] = &QImageReader::supportsOption;
    mt["text"] = &QImageReader::text;
    mt["textKeys"] = &QImageReader::textKeys;
}

int QImageReader_new(lua::state* const state)
{
    // TODO Set up object-specific methods
    // QImageReader()
    // QImageReader(QIODevice * device, const QByteArray & format = QByteArray())
    // QImageReader(const QString & fileName, const QByteArray & format = QByteArray())
    lua::make<QImageReader>(state);
    return 1;
}

int QImageReader_imageFormat(lua_State* const state)
{
    return 0;
}

int luaopen_luacxx_QImageReader(lua::state* const state)
{
    lua::thread env(state);

    env["QImageReader"] = lua::value::table;
    env["QImageReader"]["new"] = QImageReader_new;
    auto t = env["QImageReader"];

    // enum QImageReader::ImageReaderError
    t["FileNotFoundError"] = QImageReader::FileNotFoundError;
    t["DeviceError"] = QImageReader::DeviceError;
    t["UnsupportedFormatError"] = QImageReader::UnsupportedFormatError;
    t["InvalidDataError"] = QImageReader::InvalidDataError;
    t["UnknownError"] = QImageReader::UnknownError;

    t["imageFormat"] = QImageReader_imageFormat;
    t["supportedImageFormats"] = QImageReader::supportedImageFormats;
    t["supportedMimeTypes"] = &QImageReader::supportedMimeTypes;

    return 0;
}