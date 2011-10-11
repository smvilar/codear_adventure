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

	AttributeVector _objects =
			_pOwner->getAttributeAs<AttributeVector>("objects");

	for (size_t i = 0; i < _objects.size(); ++i)
	{
		string objectFilename = _objects[i]->getValue<string>();
		_pWorld->addObject(_pWorld->parseObject(objectFilename.c_str()));
	}
}
//----------------------------------------------------------------------------//
