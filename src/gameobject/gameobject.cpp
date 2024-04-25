#include "gameobject/gameobject.h"
//----------------------------------------------------------------------------//
#include <sstream>
//----------------------------------------------------------------------------//
#include "gameobject/world.h"
#include "gameobject/attribute.h"
#include "gameobject/behavior.h"
#include "gameobject/message.h"
#include "core/assert.h"
//----------------------------------------------------------------------------//
using namespace he;
//----------------------------------------------------------------------------//
GameObject::GameObject(const std::string &name)
: name(name)
, pWorld_(0)
{
}
//----------------------------------------------------------------------------//
GameObject::~GameObject()
{
	// clean attributes
	AttributeMap::iterator itAttribute = attributes_.begin();
	for (; itAttribute != attributes_.end(); ++itAttribute)
	{
		delete itAttribute->second;
	}

	// clean behaviors
	BehaviorVector::iterator itBehavior = behaviors_.begin();
	for (; itBehavior != behaviors_.end(); ++itBehavior)
		delete *itBehavior;
}
//----------------------------------------------------------------------------//
void GameObject::addAttribute(const std::string &name, Attribute *attribute)
{
	Assert(attributes_.find(name) == attributes_.end(),
		   "Error when adding attribute: another one with the same name exists");
	attributes_[name] = attribute;
}
//----------------------------------------------------------------------------//
void GameObject::removeAttribute(const std::string &name)
{
	Assert(attributes_.find(name) != attributes_.end(),
		   "Error when removing attribute: it doesn't exist");
	delete attributes_[name];
	attributes_.erase(name);
}
//----------------------------------------------------------------------------//
Attribute* GameObject::getAttribute(const std::string &name)
{
	AttributeMap::iterator it = attributes_.find(name);
	return it != attributes_.end() ? it->second : nullptr;
}
//----------------------------------------------------------------------------//
void GameObject::addBehavior(Behavior *behavior)
{
	behaviorsToAdd_.push(behavior);
}
//----------------------------------------------------------------------------//
void GameObject::removeBehavior(Behavior *behavior)
{
	behaviorsToRemove_.push(behavior);
}
//----------------------------------------------------------------------------//
Behavior* GameObject::getBehaviorByName(const std::string &name)
{
	Assert(pWorld_, "GameObject should be added to World");

	Behavior *prototype = pWorld_->createBehavior(name);
	Behavior *toFind = nullptr;

	for (size_t i = 0; i < behaviors_.size(); ++i)
	{
		if (typeid(*prototype) == typeid(*behaviors_[i]))
		{
			toFind = behaviors_[i];
			break;
		}
	}

	delete prototype;

	return toFind;
}
//----------------------------------------------------------------------------//
void GameObject::update()
{
	for (Behavior* behavior : behaviors_)
		behavior->update();
	processQueues();
}
//----------------------------------------------------------------------------//
void GameObject::broadcast(const Message &message)
{
	messages_.push(message);
}
//----------------------------------------------------------------------------//
void GameObject::removeFromWorld()
{
	Assert(pWorld_, "Error removing from world: pWorld is null");
	pWorld_->removeObject(this);
}
//----------------------------------------------------------------------------//
GameObject* GameObject::clone() const
{
	GameObject* copy = new GameObject(name);

	// clone attributes
	AttributeMap::const_iterator itAttribute = attributes_.begin();
	for (; itAttribute != attributes_.end(); ++itAttribute)
	{
		Attribute *attr = new Attribute(*itAttribute->second);
		copy->addAttribute(itAttribute->first, attr);
	}

	// clone behaviors
	BehaviorVector::const_iterator itBehavior = behaviors_.begin();
	for (; itBehavior != behaviors_.end(); ++itBehavior)
	{
		// note we're calling 'doAdd'
		copy->doAddBehavior((*itBehavior)->clone());
	}

	return copy;
}
//----------------------------------------------------------------------------//
void GameObject::added()
{
	for (Behavior* behavior : behaviors_)
	{
		behavior->pWorld_ = pWorld_;
		behavior->activate();
		behavior->update();
	}
}
//----------------------------------------------------------------------------//
void GameObject::removed()
{
	for (Behavior* behavior : behaviors_)
		behavior->deactivate();
}
//----------------------------------------------------------------------------//
void GameObject::processQueues()
{
	while (!behaviorsToAdd_.empty())
	{
		doAddBehavior(behaviorsToAdd_.front());
		behaviorsToAdd_.pop();
	}

	while (!behaviorsToRemove_.empty())
	{
		doRemoveBehavior(behaviorsToRemove_.front());
		behaviorsToRemove_.pop();
	}

	while (!messages_.empty())
	{
		doBroadcast(messages_.front());
		messages_.pop();
	}
}
//----------------------------------------------------------------------------//
void GameObject::doAddBehavior(Behavior *behavior)
{
	behaviors_.push_back(behavior);
	behavior->pOwner_ = this;
	behavior->added();
	if (pWorld_)
	{
		behavior->pWorld_ = pWorld_;
		behavior->activate();
	}
}
//----------------------------------------------------------------------------//
void GameObject::doRemoveBehavior(Behavior *behavior)
{
	if (pWorld_)
		behavior->deactivate();
	behavior->removed();
	behaviors_.erase(std::find(behaviors_.begin(), behaviors_.end(), behavior));
	delete behavior;
	behavior = nullptr;
}
//----------------------------------------------------------------------------//
void GameObject::doBroadcast(const Message &message)
{
	BehaviorVector::iterator it = behaviors_.begin();
	for (; it != behaviors_.end(); ++it)
		(*it)->handleMessage(message);
}
//----------------------------------------------------------------------------//
std::string GameObject::debugToString() const
{
	std::stringstream ss;
	ss << "- name: " << name << std::endl;
	ss << "- attributes: " << std::endl;
	AttributeMap::const_iterator it = attributes_.begin();
	for (; it != attributes_.end(); ++it)
		ss << "-- " << it->first << std::endl;
	ss << "- behaviors:" << std::endl;
	for (size_t i=0; i<behaviors_.size(); ++i)
		ss << "-- " << typeid(*behaviors_[i]).name() << std::endl;
	return ss.str();
}
//----------------------------------------------------------------------------//
