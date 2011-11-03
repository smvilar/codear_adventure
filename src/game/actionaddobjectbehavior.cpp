#include "actionaddobjectbehavior.h"
//----------------------------------------------------------------------------//
void ActionAddObjectBehavior::handleMessage(const Message &message)
{
	typedef std::vector<Attribute*> AttributeVector;

	if (message.equals("action_triggered"))
	{
		// read the args
		const AttributeVector &args = message.argsAs<AttributeVector>();
		GameObject *obj = pWorld_->createObject(args[0]->getValue<std::string>());
		std::cout << "Adding object " << obj->name << std::endl;
		std::cout << obj->debugToString() << std::endl;
		pWorld_->addObject(obj);
	}
}
//----------------------------------------------------------------------------//
