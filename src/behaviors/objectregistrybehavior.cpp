#include "behaviors/objectregistrybehavior.h"
//----------------------------------------------------------------------------//
#include "gameobject/world.h"
#include "gameobject/gameobject.h"
#include "gameobject/attribute.h"
//----------------------------------------------------------------------------//
using namespace he;
//----------------------------------------------------------------------------//
void ObjectRegistryBehavior::activate()
{
	typedef std::vector<Attribute*> AttributeVector;
	const AttributeVector &objs =
			pOwner_->getAttributeAs<AttributeVector>("objects");

	for (size_t i = 0; i < objs.size(); ++i)
	{
		std::string objectFilename = objs[i]->getValue<std::string>();
		GameObject *obj = pWorld_->parseObject(objectFilename);
		pWorld_->registerObjectPrototype(obj->name, obj);
		std::cout << "Registering " << obj->name << std::endl;
	}
}
//----------------------------------------------------------------------------//
