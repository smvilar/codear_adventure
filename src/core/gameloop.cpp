#include "core/gameloop.h"
//----------------------------------------------------------------------------//
#include "behaviors/gamebehaviors.h"
#include "gameobject/world.h"
#include "gameobject/gameobject.h"
#include "gameobject/attribute.h"
//----------------------------------------------------------------------------//
using namespace he;
//----------------------------------------------------------------------------//
void GameLoop::start(World &world, const char *gameFilename) const
{
	world.registerBehavior("Window", new WindowBehavior);
	world.registerBehavior("SceneManager", new SceneBehavior);
	world.registerBehavior("Render", new RenderBehavior);
	world.registerBehavior("FPSCounter", new FPSCounterBehavior);

	GameObject* game = world.parseObject(gameFilename);
	Attribute* isGameAlive = new Attribute(true);
	game->addAttribute("alive", isGameAlive);
	world.addObject(game);

	while (isGameAlive->getValue<bool>())
		world.update();
}
//----------------------------------------------------------------------------//
