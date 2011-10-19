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
	../lib/rapidxml-1.13 \
	../lib/zlib125/include

HEADERS += \
	../bin/data/game.json \
	../bin/data/test_scene.json \
	../bin/data/world.json \
	../bin/data/background.json \
	../bin/data/ryu.json \
	../src/hierophantengine.h \
	../src/dllexport.h \
	../src/behaviors/gamebehaviors.h \
	../src/behaviors/windowbehavior.h \
	../src/behaviors/fpscounterbehavior.h \
	../src/behaviors/loadworldstatebehavior.h \
	../src/behaviors/spritebehavior.h \
    ../src/behaviors/followmousebehavior.h \
	../src/behaviors/editbehavior.h \
	../src/behaviors/objectcontainerbehavior.h \
	../src/behaviors/spawnbehavior.h \
	../src/behaviors/textboxbehavior.h \
    ../src/core/Assert.h \
    ../src/core/Types.h \
	../src/core/Scene.h \
	../src/core/gameloop.h \
	../src/gameobject/objectparser.h \
	../src/gameobject/world.h \
	../src/gameobject/behavior.h \
	../src/gameobject/attribute.h \
    ../src/gameobject/gameobject.h \
	../src/gameobject/worldserializer.h \
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
    ../src/util/ZLib.h \
    ../src/util/Util.h \
    ../src/util/Profile.h \
    ../src/util/MemoryManager.h \
    ../src/util/Logger.h \
    ../src/util/IStoreable.h \
    ../src/util/FPSCounter.h \
    ../src/util/FileSystem.h \
	../src/util/base64.h \
	../src/video/spriteanimation.h

SOURCES += \
	../src/behaviors/spritebehavior.cpp \
	../src/behaviors/followmousebehavior.cpp \
	../src/behaviors/editbehavior.cpp \
	../src/behaviors/windowbehavior.cpp \
	../src/behaviors/fpscounterbehavior.cpp \
	../src/behaviors/objectcontainerbehavior.cpp \
	../src/behaviors/loadworldstatebehavior.cpp \
	../src/behaviors/spawnbehavior.cpp \
	../src/behaviors/textboxbehavior.cpp \
	../src/core/Scene.cpp \
	../src/core/gameloop.cpp \
	../src/gameobject/objectparser.cpp \
	../src/gameobject/world.cpp \
	../src/gameobject/behavior.cpp \
	../src/gameobject/attribute.cpp \
	../src/gameobject/gameobject.cpp \
	../src/gameobject/worldserializer.cpp \
	../src/json/json_writer.cpp \
	../src/json/json_value.cpp \
	../src/json/json_reader.cpp \
	../src/math/Vector2.cpp \
	../src/math/MathUtil.cpp \
	../src/util/ZLib.cpp \
	../src/util/Profile.cpp \
	../src/util/MemoryManager.cpp \
	../src/util/Logger.cpp \
	../src/util/IStoreable.cpp \
	../src/util/FPSCounter.cpp \
	../src/util/FileSystem.cpp \
	../src/util/base64.cpp \
	../src/video/spriteanimation.cpp \
	../src/game/main.cpp
