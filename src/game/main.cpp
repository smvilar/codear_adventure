#include "ForagersEngine.h"
#include "behaviors/gamebehaviors.h"

int main()
{
	using foragers::GameLoop;

	GameLoop gameLoop;
	gameLoop.start("game.json");

	return 0;
}
