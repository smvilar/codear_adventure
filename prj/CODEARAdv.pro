TARGET = DamageControl
QT -= core gui
TEMPLATE = app

CONFIG(debug) {
	DEFINES += _DEBUG
}

# Here we should set all the files we want
# to include in the bundle
GAME_DATA.files = ../bin/data/data.pack
GAME_DATA.path = Contents/Resources
QMAKE_BUNDLE_DATA += GAME_DATA

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
	../src/behaviors/objectregistrybehavior.h \
	../src/behaviors/behaviors.h \
	../src/core/assert.h \
	../src/core/types.h \
	../src/core/scene.h \
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
	../src/math/vector2.h \
	../src/math/rect.h \
	../src/math/mathutil.h \
	../src/resource/resourcepack.h \
	../src/resource/resourcemanager.h \
	../src/screen/screen.h \
	../src/screen/screendirector.h \
	../src/util/util.h \
	../src/util/profile.h \
	../src/util/memorymanager.h \
	../src/util/logger.h \
	../src/util/fpscounter.h \
	../src/util/filesystem.h \
	../src/util/base64.h \
	../src/util/gzstream.h \
	../src/util/mouseutil.h \
	../src/video/spriteanimation.h \
	../src/video/animatedsprite.h \
	../src/game/logobehavior.h \
	../src/game/dialogue.h \
	../src/game/dialoguenode.h \
	../src/game/dialoguecontrolbehavior.h \
	../src/game/phonecontrollerbehavior.h \
	../src/game/actionswitchtriggerbehavior.h \
	../src/game/actionsendmessagebehavior.h \
	../src/game/dialogueactorbehavior.h \
	../src/game/actionaddobjectbehavior.h \
	../src/game/actionremoveobjectbehavior.h \
	../src/game/gamescreenbehavior.h \
	../src/game/usableitembehavior.h \
	../src/game/actionaddbehaviorbehavior.h \
	../src/game/actionremovebehaviorbehavior.h

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
	../src/behaviors/objectregistrybehavior.cpp \
	../src/core/scene.cpp \
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
	../src/math/vector2.cpp \
	../src/resource/resourcepack.cpp \
	../src/resource/resourcemanager.cpp \
	../src/screen/screen.cpp \
	../src/screen/screendirector.cpp \
	../src/util/profile.cpp \
	../src/util/memorymanager.cpp \
	../src/util/logger.cpp \
	../src/util/fpscounter.cpp \
	../src/util/filesystem.cpp \
	../src/util/base64.cpp \
	../src/util/gzstream.cpp \
	../src/util/mouseutil.cpp \
	../src/video/spriteanimation.cpp \
	../src/video/animatedsprite.cpp \
	../src/game/main.cpp \
	../src/game/logobehavior.cpp \
	../src/game/dialogue.cpp \
	../src/game/dialoguenode.cpp \
	../src/game/dialoguecontrolbehavior.cpp \
	../src/game/phonecontrollerbehavior.cpp \
	../src/game/actionswitchtriggerbehavior.cpp \
	../src/game/actionsendmessagebehavior.cpp \
	../src/game/dialogueactorbehavior.cpp \
	../src/game/actionaddobjectbehavior.cpp \
	../src/game/actionremoveobjectbehavior.cpp \
	../src/game/gamescreenbehavior.cpp \
	../src/game/usableitembehavior.cpp \
	../src/game/actionaddbehaviorbehavior.cpp \
	../src/game/actionremovebehaviorbehavior.cpp
