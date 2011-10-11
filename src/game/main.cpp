#include "ForagersEngine.h"
#include "behaviors/gamebehaviors.h"

int main()
{
	using he::GameLoop;
	using he::World;

	World world;
	GameLoop gameLoop;
	gameLoop.start(world, "game.json");

	return 0;
}
