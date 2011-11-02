#include "actionsendmessagebehavior.h"
//----------------------------------------------------------------------------//
#include <vector>
#include <iostream>
//----------------------------------------------------------------------------//
void ActionSendMessageBehavior::handleMessage(const Message &message)
{
	typedef std::vector<Attribute*> AttributeVector;

	if (message.equals("action_triggered"))
	{
		// read the args
		const AttributeVector &args = message.argsAs<AttributeVector>();
		GameObject *object = pWorld_->getObject(args[0]->getValue<std::string>());
		object->broadcast(Message(args[1]->getValue<std::string>()));
	}
}
//----------------------------------------------------------------------------//
