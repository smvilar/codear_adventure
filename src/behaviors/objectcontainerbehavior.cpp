#include "behaviors/objectcontainerbehavior.h"
//----------------------------------------------------------------------------//
#include <string>
#include <vector>
//----------------------------------------------------------------------------//
#include "core/assert.h"
#include "gameobject/world.h"
#include "gameobject/gameobject.h"
//----------------------------------------------------------------------------//
using namespace he;
//----------------------------------------------------------------------------//
void ObjectContainerBehavior::added()
{
#if version_with_filenames
	using std::string;
	typedef std::vector<Attribute*> AttributeVector;

	std::vector<GameObject*> objects;

	AttributeVector objectFilenames =
			_pOwner->getAttributeAs<AttributeVector>("object_filenames");

	for (size_t i = 0; i < objectFilenames.size(); ++i)
	{
		string objectFilename = objectFilenames[i]->get<string>();
		GameObject *object = _pWorld->parseObject(objectFilename.c_str());
		objects.push_back(object);
	}

	AttributeVector objectNames =
			_pOwner->getAttributeAs<AttributeVector>("object_names");

	for (size_t i = 0; i < objectNames.size(); ++i)
	{
		string objectName = objectNames[i]->get<string>();
		GameObject *object = _pWorld->getObject(objectName.c_str());
		if (object)
			objects.push_back(object);
	}

	_pOwner->addAttribute("objects", new Attribute(objects));
	// I can clean the object_filenames attribute if I want to...
	//_pOwner->removeAttribute("object_filenames");
#endif // version_with_filenames
}
//----------------------------------------------------------------------------//
void ObjectContainerBehavior::activate()
{
	using std::string;
	typedef std::vector<Attribute*> AttributeVector;

	std::vector<GameObject*> objects;

	AttributeVector objectNames =
			pOwner_->getAttributeAs<AttributeVector>("object_names");

	for (size_t i = 0; i < objectNames.size(); ++i)
	{
		string objectName = objectNames[i]->get<string>();
		GameObject *object = pWorld_->getObject(objectName);
		if (object)
			objects.push_back(object);
	}

	pOwner_->addAttribute("objects", new Attribute(objects));
}
//----------------------------------------------------------------------------//
Behavior* ObjectContainerBehavior::clone() const
{
	return new ObjectContainerBehavior;
}
//----------------------------------------------------------------------------//
