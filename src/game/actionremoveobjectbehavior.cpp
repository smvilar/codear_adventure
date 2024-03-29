#include "actionremoveobjectbehavior.h"
//----------------------------------------------------------------------------//
void ActionRemoveObjectBehavior::handleMessage(const Message &message)
{
	typedef std::vector<Attribute*> AttributeVector;

	if (message.equals("action_triggered"))
	{
		// read the args
		const AttributeVector &args = message.argsAs<AttributeVector>();
		pWorld_->removeObject(args[0]->get<std::string>());
	}
}
//----------------------------------------------------------------------------//
