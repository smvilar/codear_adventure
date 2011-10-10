TARGET = CODEARAdv
QT -= core gui
TEMPLATE = app

CONFIG(debug) {
	DEFINES += _DEBUG
}

OBJECTS_DIR = ../obj

mac:LIBS += \
	-framework CoreFoundation \
	-framework OpenGL

win32:LIBS += \
	-L../lib/SFML/lib/mingw \
	-lopengl32 \
	-lglu32

LIBS += \
	-lsfml-system \
	-lsfml-window \
	-lsfml-graphics \
	-lsfml-audio

INCLUDEPATH += \
	../src \
	../lib \
	../lib/SFML/include \
	../lib/freetype/include \
	../lib/rapidxml-1.13 \
	../lib/zlib125/include

HEADERS += \
	../src/foragersengine.h \
	../src/dllexport.h \
	../src/behaviors/spritebehavior.h \
    ../src/behaviors/followmousebehavior.h \
    ../src/behaviors/editbehavior.h \
	../src/behaviors/scenemanager.h \
	../src/behaviors/windowbehavior.h \
	../src/behaviors/renderbehavior.h \
	../src/behaviors/gamebehaviors.h \
    ../src/core/Assert.h \
    ../src/core/Types.h \
	../src/core/Scene.h \
	../src/core/Entity.h \
	../src/core/BaseObject.h \
	../src/core/GameLoop.h \
    ../src/gameobject/objectparser.h \
    ../src/gameobject/goworld.h \
    ../src/gameobject/gobehavior.h \
    ../src/gameobject/goattribute.h \
    ../src/gameobject/gameobject.h \
    ../src/json/writer.h \
    ../src/json/value.h \
    ../src/json/reader.h \
    ../src/json/json.h \
    ../src/json/json_batchallocator.h \
    ../src/json/forwards.h \
    ../src/json/features.h \
    ../src/json/config.h \
    ../src/json/autolink.h \
    ../src/math/Vector2.h \
    ../src/math/Rect.h \
    ../src/math/MathUtil.h \
    ../src/resource/ResourceManager.h \
    ../src/resource/IResource.h \
    ../src/resource/Font.h \
    ../src/util/ZLib.h \
    ../src/util/Util.h \
    ../src/util/Profile.h \
    ../src/util/MemoryManager.h \
    ../src/util/Logger.h \
    ../src/util/IStoreable.h \
    ../src/util/FPSCounter.h \
    ../src/util/FileSystem.h \
    ../src/util/base64.h \
    ../src/video/Vertex.h \
    ../src/video/Tilemap.h \
    ../src/video/Texture.h \
    ../src/video/Text.h \
    ../src/video/StaticVertexBuffer.h \
    ../src/video/Sprite.h \
	../src/video/Shape.h \
    ../src/video/Renderer.h \
    ../src/video/GLee.h \
    ../src/video/ForagersEngine.h \
    ../src/video/DynamicVertexBuffer.h \
    ../src/video/DllExport.h \
	../src/video/Color.h

SOURCES += \
	../src/behaviors/spritebehavior.cpp \
	../src/behaviors/followmousebehavior.cpp \
	../src/behaviors/editbehavior.cpp \
	../src/behaviors/scenemanager.cpp \
	../src/behaviors/windowbehavior.cpp \
	../src/behaviors/renderbehavior.cpp \
	../src/core/Scene.cpp \
	../src/core/GameLoop.cpp \
	../src/gameobject/objectparser.cpp \
	../src/gameobject/goworld.cpp \
	../src/gameobject/gobehavior.cpp \
	../src/gameobject/goattribute.cpp \
	../src/gameobject/gameobject.cpp \
	../src/json/json_writer.cpp \
	../src/json/json_value.cpp \
	../src/json/json_reader.cpp \
	../src/math/Vector2.cpp \
	../src/math/MathUtil.cpp \
	../src/resource/ResourceManager.cpp \
#	../src/resource/Font.cpp \
	../src/util/ZLib.cpp \
	../src/util/Profile.cpp \
	../src/util/MemoryManager.cpp \
	../src/util/Logger.cpp \
	../src/util/IStoreable.cpp \
	../src/util/FPSCounter.cpp \
	../src/util/FileSystem.cpp \
	../src/util/base64.cpp \
	../src/video/Tilemap.cpp \
	../src/video/Texture.cpp \
#	../src/video/Text.cpp \
	../src/video/StaticVertexBuffer.cpp \
	../src/video/Sprite.cpp \
	../src/video/Shape.cpp \
	../src/video/Renderer.cpp \
	../src/video/GLee.c \
	../src/video/DynamicVertexBuffer.cpp \
	../src/video/Color.cpp \
	../src/game/main.cpp
