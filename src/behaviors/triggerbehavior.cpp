#include "behaviors/triggerbehavior.h"
//----------------------------------------------------------------------------//
#include <iostream>
#include <map>
//----------------------------------------------------------------------------//
#include "gameobject/gameobject.h"
#include "gameobject/message.h"
#include "gameobject/world.h"
//----------------------------------------------------------------------------//
using namespace he;
//----------------------------------------------------------------------------//
void TriggerBehavior::handleMessage(const Message &message)
{
	if (message.equals("trigger_condition"))
	{
		std::string condition = message.argsAs<std::string>();
		std::cout << "Condition " << condition << " triggered." << std::endl;

		for (size_t i = 0; i < conditions_.size(); ++i)
		{
			Condition &c = conditions_[i];
			if (!c.met && c.name == condition)
			{
				c.met = true;
				break;
			}
		}
		if (allConditionsMet())
		{
			doActions();
		}
	}
}
//----------------------------------------------------------------------------//
void TriggerBehavior::activate()
{
	typedef std::vector<Attribute*> AttributeVector;
	typedef std::map<std::string, Attribute*> AttributeMap;

	AttributeVector conditions = pOwner_->getAttributeAs<AttributeVector>("conditions");
	conditions_.reserve(conditions.size());
	for (size_t i = 0; i < conditions.size(); ++i)
	{
		conditions_.push_back(conditions[i]->getValue<std::string>());
	}

	AttributeVector actions = pOwner_->getAttributeAs<AttributeVector>("actions");
	actions_.reserve(actions.size());
	for (size_t i = 0; i < actions.size(); ++i)
	{
		AttributeMap actionObj = actions[i]->getValue<AttributeMap>();
		AttributeMap::iterator it = actionObj.begin();
		for (; it != actionObj.end(); ++it)
		{
			actions_.push_back(Action(actionObj["action"]->getValue<std::string>(),
									  actionObj["args"]->getValue<AttributeVector>()));
		}
	}
}
//----------------------------------------------------------------------------//
bool TriggerBehavior::allConditionsMet() const
{
	for (size_t i = 0; i < conditions_.size(); ++i)
	{
		if (!conditions_[i].met) return false;
	}
	return true;
}
//----------------------------------------------------------------------------//
void TriggerBehavior::doActions()
{
	std::cout << "Doing actions" << std::endl;
	for (size_t i = 0; i < actions_.size(); ++i)
	{
		pWorld_->broadcast(Message(actions_[i].name, actions_[i].args));
	}
}
//----------------------------------------------------------------------------//
