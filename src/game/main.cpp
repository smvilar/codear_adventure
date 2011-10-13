#include "hierophantengine.h"
#include "behaviors/gamebehaviors.h"
#include "behaviors/spritebehavior.h"
#include "behaviors/editbehavior.h"

using namespace he;

void setupWorld(World &world)
{
	world.registerBehavior("Sprite", new SpriteBehavior);
	world.registerBehavior("Edit", new EditBehavior);
}

int main()
{
	World world;
	setupWorld(world);

	GameLoop gameLoop;
	gameLoop.start(world, "game.json");

	return 0;
}
