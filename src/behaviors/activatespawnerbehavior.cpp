#include "behaviors/activatespawnerbehavior.h"
//----------------------------------------------------------------------------//
#include "gameobject/world.h"
#include "gameobject/gameobject.h"
#include "behaviors/spawnbehavior.h"
//----------------------------------------------------------------------------//
using namespace he;
//----------------------------------------------------------------------------//
void ActivateSpawnerBehavior::activate()
{
	using std::string;

	_pWorld->registerBehavior("Spawn", new SpawnBehavior);
	string spawnerFilename = _pOwner->getAttributeAs<string>("spawner");

	_pWorld->addObject(_pWorld->parseObject(spawnerFilename.c_str()));
}
//----------------------------------------------------------------------------//
Behavior* ActivateSpawnerBehavior::clone() const
{
	return new ActivateSpawnerBehavior;
}
//----------------------------------------------------------------------------//
