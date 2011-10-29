#include <hierophantengine.h>
//----------------------------------------------------------------------------//
#include "logobehavior.h"
#include "dialoguecontrolbehavior.h"
#include "conditiononclickbehavior.h"
#include "addbehaviorbehavior.h"
#include "phonecontrollerbehavior.h"
//----------------------------------------------------------------------------//
using namespace he;
//----------------------------------------------------------------------------//
void setupWorld(World &world)
{
	// game specific
	world.registerBehavior("Logo", new LogoBehavior);
	world.registerBehavior("DialogueControl", new DialogueControlBehavior);
	world.registerBehavior("ConditionOnClick", new ConditionOnClickBehavior);
	world.registerBehavior("AddBehavior", new AddBehaviorBehavior);
	world.registerBehavior("PhoneController", new PhoneControllerBehavior);
}
//----------------------------------------------------------------------------//
int main()
{
	World world;
	world.addResourcePack("data.pack");
	setupWorld(world);

	GameLoop gameLoop;
	gameLoop.start(world, "game.json");

	return 0;
}
//----------------------------------------------------------------------------//
