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
		GameObject *object = pWorld_->getObject(args[0]->get<std::string>());
		const std::string &messageName = args[1]->get<std::string>();
		if (args.size() < 3)
			object->broadcast(Message(messageName));
		else
		{
			const std::string &arg = args[2]->get<std::string>();
			object->broadcast(Message(messageName, arg));
		}
	}
}
//----------------------------------------------------------------------------//
