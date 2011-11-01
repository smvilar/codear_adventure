#include <hierophantengine.h>
//----------------------------------------------------------------------------//
#include "logobehavior.h"
#include "dialoguecontrolbehavior.h"
#include "conditiononclickbehavior.h"
#include "phonecontrollerbehavior.h"
#include "dialogueactorbehavior.h"
#include "actionsendmessagebehavior.h"
#include "actionswitchtriggerbehavior.h"
//----------------------------------------------------------------------------//
using namespace he;
//----------------------------------------------------------------------------//
void setupWorld(World &world)
{
	// game specific
	world.registerBehavior("Logo", new LogoBehavior);
	world.registerBehavior("DialogueControl", new DialogueControlBehavior);
	world.registerBehavior("ConditionOnClick", new ConditionOnClickBehavior);
	world.registerBehavior("PhoneController", new PhoneControllerBehavior);
	world.registerBehavior("DialogueActor", new DialogueActorBehavior);
	world.registerBehavior("ActionSendMessage", new ActionSendMessageBehavior);
	world.registerBehavior("ActionSwitchTrigger", new ActionSwitchTriggerBehavior);
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
