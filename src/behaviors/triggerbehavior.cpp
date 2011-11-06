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

		for (size_t i = 0; i < conditions_.size(); ++i)
		{
			Condition &c = conditions_[i];
			if (!c.met && c.name == condition)
			{
				std::cout << "Condition " << condition << " met." << std::endl;
				c.met = true;
				if (allConditionsMet())
				{
					doActions();
				}
				break;
			}
		}
	}
	else if (message.equals("trigger_switch"))
	{
		active_ = message.argsAs<bool>();
		std::cout << "Switching trigger " << pOwner_->name << ": " << active_ << std::endl;
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
		conditions_.push_back(conditions[i]->get<std::string>());
	}

	AttributeVector actions = pOwner_->getAttributeAs<AttributeVector>("actions");
	actions_.reserve(actions.size());
	for (size_t i = 0; i < actions.size(); ++i)
	{
		AttributeMap actionObj = actions[i]->get<AttributeMap>();
		actions_.push_back(Action(actionObj["action"]->get<std::string>(),
								  actionObj["args"]->get<AttributeVector>()));
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
	if (!active_) return;
	active_ = false;
	std::cout << "Doing actions (" << actions_.size() << ")" << std::endl;
	for (size_t i = 0; i < actions_.size(); ++i)
	{
		std::cout << "Action: " << actions_[i].name << std::endl;
		GameObject *actionObject = pWorld_->getObject(actions_[i].name);
		if (actionObject)
			actionObject->broadcast(Message("action_triggered", actions_[i].args));
		else
			pWorld_->broadcast(Message(actions_[i].name, actions_[i].args));
	}
}
//----------------------------------------------------------------------------//
