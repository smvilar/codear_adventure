#ifndef HE_BEHAVIORS_H
#define HE_BEHAVIORS_H
//----------------------------------------------------------------------------//
#include "spritebehavior.h"
#include "editbehavior.h"
#include "objectcontainerbehavior.h"
#include "textboxbehavior.h"
#include "textinputbehavior.h"
#include "soundplayerbehavior.h"
#include "musicplayerbehavior.h"
//----------------------------------------------------------------------------//
#include "gameobject/world.h"
//----------------------------------------------------------------------------//
namespace he {
//----------------------------------------------------------------------------//
namespace Behaviors {
//----------------------------------------------------------------------------//
void registerToWorld(World& world)
{
	world.registerBehavior("Sprite", new SpriteBehavior);
	world.registerBehavior("Edit", new EditBehavior);
	world.registerBehavior("ObjectContainer", new ObjectContainerBehavior);
	world.registerBehavior("TextBox", new TextBoxBehavior);
	world.registerBehavior("TextInput", new TextInputBehavior);
	world.registerBehavior("SoundPlayer", new SoundPlayerBehavior);
	world.registerBehavior("MusicPlayer", new MusicPlayerBehavior);
}
//----------------------------------------------------------------------------//
} // end namespace Behaviors
//----------------------------------------------------------------------------//
} // end namespace he
//----------------------------------------------------------------------------//
#endif // HE_BEHAVIORS_H
