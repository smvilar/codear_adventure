TARGET = CODEARAdv
QT -= core gui
TEMPLATE = app

CONFIG(debug) {
	DEFINES += _DEBUG
}

# Here we should set all the files we want
# to include in the bundle
#GAME_DATA.files = ../bin/data/walk.png
#GAME_DATA.path = Contents/MacOS
#QMAKE_BUNDLE_DATA += GAME_DATA

# Here we can specify the icon for the bundle
#ICON =

# this is supposed to force the compilation
# when a header has changed...
DEPENDPATH += ../include

OBJECTS_DIR = ../obj

mac:LIBS += \
	-framework CoreFoundation \
	-framework OpenGL \
	-lz

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
	../lib/SFML/include

HEADERS += \
	../bin/data/game.json \
	../bin/data/screen_flow.json \
	../bin/data/screen_game.json \
	../bin/data/screen_logo.json \
	../bin/data/test_dialogue.json \
	../bin/data/sprite_info_mc.json \
	../bin/data/sprite_info_bkg.json \
	../src/hierophantengine.h \
	../src/dllexport.h \
	../src/behaviors/windowbehavior.h \
	../src/behaviors/fpscounterbehavior.h \
	../src/behaviors/spritebehavior.h \
	../src/behaviors/shapebehavior.h \
	../src/behaviors/editbehavior.h \
	../src/behaviors/objectcontainerbehavior.h \
	../src/behaviors/screendirectorbehavior.h \
	../src/behaviors/spawnbehavior.h \
	../src/behaviors/textboxbehavior.h \
	../src/behaviors/textinputbehavior.h \
	../src/behaviors/soundplayerbehavior.h \
	../src/behaviors/musicplayerbehavior.h \
	../src/behaviors/triggerbehavior.h \
	../src/behaviors/behaviors.h \
	../src/core/Assert.h \
	../src/core/Types.h \
	../src/core/Scene.h \
	../src/core/gameloop.h \
	../src/gameobject/objectparser.h \
	../src/gameobject/world.h \
	../src/gameobject/world.inl \
	../src/gameobject/behavior.h \
	../src/gameobject/attribute.h \
	../src/gameobject/gameobject.h \
	../src/gameobject/worldserializer.h \
	../src/gameobject/message.h \
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
	../src/screen/screen.h \
	../src/screen/screendirector.h \
	../src/util/Util.h \
	../src/util/Profile.h \
	../src/util/MemoryManager.h \
	../src/util/Logger.h \
	../src/util/FPSCounter.h \
	../src/util/FileSystem.h \
	../src/util/base64.h \
	../src/util/gzstream.h \
	../src/video/spriteanimation.h \
	../src/video/animatedsprite.h \
	../src/game/logobehavior.h \
	../src/game/dialogue.h \
	../src/game/dialoguenode.h \
	../src/game/dialoguecontrolbehavior.h \
	../src/game/conditiononclickbehavior.h \
	../src/game/addbehaviorbehavior.h \
	../src/game/phonecontrollerbehavior.h

SOURCES += \
	../src/behaviors/spritebehavior.cpp \
	../src/behaviors/shapebehavior.cpp \
	../src/behaviors/editbehavior.cpp \
	../src/behaviors/windowbehavior.cpp \
	../src/behaviors/fpscounterbehavior.cpp \
	../src/behaviors/objectcontainerbehavior.cpp \
	../src/behaviors/screendirectorbehavior.cpp \
	../src/behaviors/spawnbehavior.cpp \
	../src/behaviors/textboxbehavior.cpp \
	../src/behaviors/textinputbehavior.cpp \
	../src/behaviors/soundplayerbehavior.cpp \
	../src/behaviors/musicplayerbehavior.cpp \
	../src/behaviors/triggerbehavior.cpp \
	../src/core/Scene.cpp \
	../src/core/gameloop.cpp \
	../src/gameobject/objectparser.cpp \
	../src/gameobject/world.cpp \
	../src/gameobject/behavior.cpp \
	../src/gameobject/attribute.cpp \
	../src/gameobject/gameobject.cpp \
	../src/gameobject/worldserializer.cpp \
	../src/gameobject/message.cpp \
	../src/json/json_writer.cpp \
	../src/json/json_value.cpp \
	../src/json/json_reader.cpp \
	../src/math/Vector2.cpp \
	../src/screen/screen.cpp \
	../src/screen/screendirector.cpp \
	../src/util/Profile.cpp \
	../src/util/MemoryManager.cpp \
	../src/util/Logger.cpp \
	../src/util/FPSCounter.cpp \
	../src/util/FileSystem.cpp \
	../src/util/base64.cpp \
	../src/util/gzstream.cpp \
	../src/video/spriteanimation.cpp \
	../src/video/animatedsprite.cpp \
	../src/game/main.cpp \
	../src/game/logobehavior.cpp \
	../src/game/dialogue.cpp \
	../src/game/dialoguenode.cpp \
	../src/game/dialoguecontrolbehavior.cpp \
	../src/game/conditiononclickbehavior.cpp \
	../src/game/addbehaviorbehavior.cpp \
	../src/game/phonecontrollerbehavior.cpp




