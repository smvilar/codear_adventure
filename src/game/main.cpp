#include <hierophantengine.h>
//----------------------------------------------------------------------------//
#include "logobehavior.h"
#include "dialoguecontrolbehavior.h"
#include "phonecontrollerbehavior.h"
#include "dialogueactorbehavior.h"
#include "actionsendmessagebehavior.h"
#include "actionswitchtriggerbehavior.h"
#include "actionaddobjectbehavior.h"
#include "actionremoveobjectbehavior.h"
#include "gamescreenbehavior.h"
#include "usableitembehavior.h"
//----------------------------------------------------------------------------//
using namespace he;
//----------------------------------------------------------------------------//
void setupWorld(World &world)
{
	// game specific
	world.registerBehavior("Logo", new LogoBehavior);
	world.registerBehavior("GameScreen", new GameScreenBehavior);
	world.registerBehavior("DialogueControl", new DialogueControlBehavior);
	world.registerBehavior("PhoneController", new PhoneControllerBehavior);
	world.registerBehavior("DialogueActor", new DialogueActorBehavior);
	world.registerBehavior("ActionSendMessage", new ActionSendMessageBehavior);
	world.registerBehavior("ActionSwitchTrigger", new ActionSwitchTriggerBehavior);
	world.registerBehavior("ActionAddObject", new ActionAddObjectBehavior);
	world.registerBehavior("ActionRemoveObject", new ActionRemoveObjectBehavior);
	world.registerBehavior("UsableItem", new UsableItemBehavior);
}
//----------------------------------------------------------------------------//
int main()
{
	World world;
	world.getResourceManager().addResourcePack("data.pack");
	setupWorld(world);

	GameLoop gameLoop;
	gameLoop.start(world, "config/game.json");

	return 0;
}
//----------------------------------------------------------------------------//
