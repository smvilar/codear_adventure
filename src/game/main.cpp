#include "ForagersEngine.h"
#include "behaviors/gamebehaviors.h"
#include "behaviors/spritebehavior.h"

using namespace he;

void setupWorld(World &world)
{
	world.registerBehavior("Sprite", new SpriteBehavior);
}

int main()
{
	World world;
	setupWorld(world);

	GameLoop gameLoop;
	gameLoop.start(world, "game.json");

	return 0;
}
