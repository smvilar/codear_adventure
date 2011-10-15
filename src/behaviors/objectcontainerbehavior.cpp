#include "behaviors/objectcontainerbehavior.h"
//----------------------------------------------------------------------------//
#include <string>
#include <vector>
//----------------------------------------------------------------------------//
#include "gameobject/world.h"
#include "gameobject/gameobject.h"
//----------------------------------------------------------------------------//
using namespace he;
//----------------------------------------------------------------------------//
void ObjectContainerBehavior::added()
{
	using std::string;
	typedef std::vector<Attribute*> AttributeVector;

	AttributeVector objectFilenames =
			_pOwner->getAttributeAs<AttributeVector>("object_filenames");

	std::vector<GameObject*> objects;

	for (size_t i = 0; i < objectFilenames.size(); ++i)
	{
		string objectFilename = objectFilenames[i]->getValue<string>();
		GameObject *object = _pWorld->parseObject(objectFilename.c_str());
		objects.push_back(object);
	}

	_pOwner->addAttribute("objects", new Attribute(objects));
	// I can clean the object_filenames attribute if I want to...
	//_pOwner->removeAttribute("object_filenames");
}
//----------------------------------------------------------------------------//
Behavior* ObjectContainerBehavior::clone() const
{
	return new ObjectContainerBehavior;
}
//----------------------------------------------------------------------------//
