#include "addbehaviorbehavior.h"
//----------------------------------------------------------------------------//
void AddBehaviorBehavior::handleMessage(const Message &message)
{
	if (message.equals("action_add_behavior"))
	{
		Behavior *behavior = pWorld_->createBehavior(behaviorToAdd_.c_str());
		pWorld_->getObject(target_.c_str())->addBehavior(behavior);
	}
}
//----------------------------------------------------------------------------//
void AddBehaviorBehavior::added()
{
	target_ = pOwner_->getAttributeAs<std::string>("target");
	behaviorToAdd_ = pOwner_->getAttributeAs<std::string>("behaviorToAdd");
}
//----------------------------------------------------------------------------//
