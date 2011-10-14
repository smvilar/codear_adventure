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
	using std::string;
	typedef std::vector<Attribute*> AttributeVector;

	AttributeVector objects =
			_pOwner->getAttributeAs<AttributeVector>("objects");

	for (size_t i = 0; i < objects.size(); ++i)
	{
		string objectFilename = objects[i]->getValue<string>();
		_pWorld->addObject(_pWorld->parseObject(objectFilename.c_str()));
	}
}
//----------------------------------------------------------------------------//
