#include "actionremovebehaviorbehavior.h"
//----------------------------------------------------------------------------//
void ActionRemoveBehaviorBehavior::handleMessage(const Message &message)
{
	typedef std::vector<Attribute*> AttributeVector;

	if (message.equals("action_triggered"))
	{
		// read the args
		const AttributeVector &args = message.argsAs<AttributeVector>();
		GameObject *obj = pWorld_->getObject(args[0]->get<std::string>());
		Behavior *behavior = obj->getBehaviorByName(args[1]->get<std::string>());
		if (behavior)
			obj->removeBehavior(behavior);
	}
}
//----------------------------------------------------------------------------//
