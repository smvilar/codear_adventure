#include "core/gameloop.h"
//----------------------------------------------------------------------------//
#include "gameobject/world.h"
#include "gameobject/gameobject.h"
#include "gameobject/attribute.h"
#include "behaviors/gamebehaviors.h"
//----------------------------------------------------------------------------//
using namespace he;
//----------------------------------------------------------------------------//
void GameLoop::start(World &world, const char *gameFilename) const
{
	world.registerBehavior("Window", new WindowBehavior);
	world.registerBehavior("SceneManager", new SceneBehavior);
	world.registerBehavior("Render", new RenderBehavior);
	world.registerBehavior("FPSCounter", new FPSCounterBehavior);
	world.registerBehavior("ActivateSpawner", new ActivateSpawnerBehavior);
	world.registerBehavior("LoadWorldState", new LoadWorldStateBehavior);

	GameObject* game = world.parseObject(gameFilename);
	Attribute* isGameAlive = new Attribute(true);
	game->addAttribute("alive", isGameAlive);
	world.addObject(game);
	world.getWorldSerializer().addIgnoredObject(game->name.c_str());

	while (isGameAlive->getValue<bool>())
		world.update();
}
//----------------------------------------------------------------------------//
