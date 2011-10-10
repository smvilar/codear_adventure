#include "ForagersEngine.h"

int main()
{
	using foragers::Game;

	Game game("game.json");

	game.run();

	return 0;
}
