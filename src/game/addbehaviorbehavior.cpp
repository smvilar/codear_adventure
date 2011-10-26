#include "addbehaviorbehavior.h"
//----------------------------------------------------------------------------//
void AddBehaviorBehavior::handleMessage(const Message &message)
{
	if (message.equals("ActionAddBehavior"))
	{
		typedef std::vector<Attribute*> AttributeVector;
		const AttributeVector &args = message.argsAs<AttributeVector>();
		const std::string &target = args[0]->getValue<std::string>();
		const std::string &behaviorToAdd = args[1]->getValue<std::string>();
		std::cout << "AddBehavior: " << behaviorToAdd << " to " << target << std::endl;
		Behavior *behavior = pWorld_->createBehavior(behaviorToAdd);
		pWorld_->getObject(target)->addBehavior(behavior);
	}
}
//----------------------------------------------------------------------------//
void AddBehaviorBehavior::added()
{
}
//----------------------------------------------------------------------------//
