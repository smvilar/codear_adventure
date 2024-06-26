#include "core/gameloop.h"
//----------------------------------------------------------------------------//
#include "gameobject/world.h"
#include "gameobject/gameobject.h"
#include "gameobject/attribute.h"
#include "behaviors/windowbehavior.h"
#include "behaviors/fpscounterbehavior.h"
#include "behaviors/screendirectorbehavior.h"
//----------------------------------------------------------------------------//
using namespace he;
//----------------------------------------------------------------------------//
void GameLoop::start(World &world, const char *gameFilename) const
{
	GameObject* game = world.parseObject(gameFilename);
	game->name = "Game";
	Attribute* isGameAlive = new Attribute(true);
	game->addAttribute("alive", isGameAlive);
	game->addBehavior(new WindowBehavior);
	game->addBehavior(new FPSCounterBehavior);
	game->addBehavior(new ScreenDirectorBehavior);

	world.addObject(game);
	world.getWorldSerializer().addIgnoredObject(game->name);

	while (isGameAlive->get<bool>())
		world.update();
}
//----------------------------------------------------------------------------//
