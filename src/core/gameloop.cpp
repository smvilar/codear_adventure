#include "core/gameloop.h"
//----------------------------------------------------------------------------//
#include "behaviors/gamebehaviors.h"
#include "gameobject/goworld.h"
#include "gameobject/gameobject.h"
#include "gameobject/goattribute.h"
//----------------------------------------------------------------------------//
using namespace foragers;
//----------------------------------------------------------------------------//
void GameLoop::start(const char *gameFilename) const
{
	World world;
	world.registerBehavior("SceneManager", new SceneManager);
	world.registerBehavior("Render", new RenderBehavior);
	world.registerBehavior("Window", new WindowBehavior);

	GameObject* game = world.parseObject(gameFilename);
	Attribute* isGameAlive = new Attribute(true);
	game->addAttribute("alive", isGameAlive);
	world.addObject(game);

	while (isGameAlive->getValue<bool>())
		world.update();
}
//----------------------------------------------------------------------------//
