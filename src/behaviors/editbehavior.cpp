#include "behaviors/editbehavior.h"
//----------------------------------------------------------------------------//
#include <iostream>
#include "gameobject/gameobject.h"
#include "gameobject/world.h"
//----------------------------------------------------------------------------//
using namespace he;
//----------------------------------------------------------------------------//
Behavior* EditBehavior::clone() const
{
	return new EditBehavior;
}
//----------------------------------------------------------------------------//
void EditBehavior::activate()
{
	using std::string;
	typedef std::vector<Attribute*> AttributeVector;

	AttributeVector objects =
			_pOwner->getAttributeAs<AttributeVector>("objects");

	for (size_t i = 0; i < objects.size(); ++i)
	{
		string objectFilename = objects[i]->getValue<string>();
		GameObject *dummyObject = _pWorld->parseObject(objectFilename.c_str());
		if (GameObject *obj = _pWorld->getObject(dummyObject->name.c_str()))
		{
			std::cout << "Adding " << obj << std::endl;
			_objects.push_back(obj);
		}
		delete dummyObject;
	}
}
//----------------------------------------------------------------------------//
