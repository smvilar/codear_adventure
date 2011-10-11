#include "ForagersEngine.h"
#include "behaviors/gamebehaviors.h"

int main()
{
	using foragers::GameLoop;
	using foragers::World;

	World world;
	GameLoop gameLoop;
	gameLoop.start(world, "game.json");

	return 0;
}
