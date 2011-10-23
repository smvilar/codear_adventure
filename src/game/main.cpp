#include "hierophantengine.h"
#include "logobehavior.h"

using namespace he;

void setupWorld(World &world)
{
	// game specific
	world.registerBehavior("Logo", new LogoBehavior);
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
