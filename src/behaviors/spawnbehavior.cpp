#include "behaviors/spawnbehavior.h"
//----------------------------------------------------------------------------//
#include <vector>
//----------------------------------------------------------------------------//
#include "gameobject/gameobject.h"
#include "gameobject/world.h"
//----------------------------------------------------------------------------//
using namespace he;
//----------------------------------------------------------------------------//
Behavior* SpawnBehavior::clone() const
{
	return new SpawnBehavior;
}
//----------------------------------------------------------------------------//
void SpawnBehavior::activate()
{
	typedef std::vector<GameObject*> GameObjectVector;

	GameObjectVector objects =
			_pOwner->getAttributeAs<GameObjectVector>("objects");

	for (size_t i = 0; i < objects.size(); ++i)
	{
		_pWorld->addObject(objects[i]);
	}
}
//----------------------------------------------------------------------------//
