#include <hierophantengine.h>
//----------------------------------------------------------------------------//
#include "logobehavior.h"
#include "dialoguecontrolbehavior.h"
#include "conditiononclickbehavior.h"
#include "phonecontrollerbehavior.h"
#include "actionsendmessagebehavior.h"
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
	world.registerBehavior("ActionSendMessage", new ActionSendMessageBehavior);
}
//----------------------------------------------------------------------------//
int main()
{
	World world;
	world.getResourceManager().addResourcePack("data.pack");
	setupWorld(world);

	GameLoop gameLoop;
	gameLoop.start(world, "game.json");

	return 0;
}
//----------------------------------------------------------------------------//
