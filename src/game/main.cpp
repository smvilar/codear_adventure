#include "hierophantengine.h"
#include "behaviors/gamebehaviors.h"
#include "behaviors/spritebehavior.h"
#include "behaviors/editbehavior.h"
#include "behaviors/objectcontainerbehavior.h"

using namespace he;

void setupWorld(World &world)
{
	world.registerBehavior("Sprite", new SpriteBehavior);
	world.registerBehavior("Edit", new EditBehavior);
	world.registerBehavior("ObjectContainer", new ObjectContainerBehavior);
}

int main()
{
	World world;
	setupWorld(world);

	GameLoop gameLoop;
	gameLoop.start(world, "game.json");
	//world.saveState("test_scene.json");

	return 0;
}
