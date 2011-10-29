#include "gameobject/gameobject.h"
//----------------------------------------------------------------------------//
#include "gameobject/world.h"
#include "gameobject/attribute.h"
#include "gameobject/behavior.h"
#include "core/assert.h"
//----------------------------------------------------------------------------//
using namespace he;
//----------------------------------------------------------------------------//
GameObject::GameObject(const char *name)
: name(name)
, pWorld_(0)
{
}
//----------------------------------------------------------------------------//
GameObject::~GameObject()
{
	// clean behaviors
	BehaviorVector::iterator itBehavior = behaviors_.begin();
	for (; itBehavior != behaviors_.end(); ++itBehavior)
		delete *itBehavior;

	// clean attributes
	AttributeMap::iterator itAttribute = attributes_.begin();
	for (; itAttribute != attributes_.end(); ++itAttribute)
		delete itAttribute->second;
}
//----------------------------------------------------------------------------//
void GameObject::addBehavior(Behavior *behavior)
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
void GameObject::removeBehavior(Behavior *behavior)
{
	if (pWorld_)
		behavior->deactivate();
	behavior->removed();
	behaviors_.erase(std::find(behaviors_.begin(), behaviors_.end(), behavior));
	delete behavior;
	behavior = 0;
}
//----------------------------------------------------------------------------//
void GameObject::addAttribute(const char *name, Attribute *attribute)
{
	Assert(attributes_.find(name) == attributes_.end(),
		   "Error when adding attribute: another one with the same name exists");
	attributes_[name] = attribute;
}
//----------------------------------------------------------------------------//
void GameObject::removeAttribute(const char *name)
{
	Assert(attributes_.find(name) != attributes_.end(),
		   "Error when removing attribute: it doesn't exist");
	delete attributes_[name];
	attributes_.erase(name);
}
//----------------------------------------------------------------------------//
Attribute* GameObject::getAttribute(const char *name)
{
	AttributeMap::iterator it = attributes_.find(name);
	return it != attributes_.end() ? it->second : 0;
}
//----------------------------------------------------------------------------//
void GameObject::update()
{
	BehaviorVector::iterator it = behaviors_.begin();
	for (; it != behaviors_.end(); ++it)
		(*it)->update();
}
//----------------------------------------------------------------------------//
void GameObject::broadcast(const Message &message)
{
	BehaviorVector::iterator it = behaviors_.begin();
	for (; it != behaviors_.end(); ++it)
		(*it)->handleMessage(message);
}
//----------------------------------------------------------------------------//
void GameObject::removeFromWorld()
{
	Assert(pWorld_, "Error removing from world: pWorld is a null pointer");
	pWorld_->removeObject(this);
}
//----------------------------------------------------------------------------//
GameObject* GameObject::clone() const
{
	GameObject* copy = new GameObject(name.c_str());

	// clone behaviors
	BehaviorVector::const_iterator itBehavior = behaviors_.begin();
	for (; itBehavior != behaviors_.end(); ++itBehavior)
	{
		copy->addBehavior((*itBehavior)->clone());
	}

	// clone attributes
	AttributeMap::const_iterator itAttribute = attributes_.begin();
	for (; itAttribute != attributes_.end(); ++itAttribute)
	{
		copy->addAttribute(itAttribute->first.c_str(), itAttribute->second);
	}

	return copy;
}
//----------------------------------------------------------------------------//
void GameObject::added()
{
	BehaviorVector::iterator it = behaviors_.begin();
	for (; it != behaviors_.end(); ++it)
	{
		Behavior* behavior = *it;
		behavior->pWorld_ = pWorld_;
		behavior->activate();
	}
}
//----------------------------------------------------------------------------//
void GameObject::removed()
{
	BehaviorVector::iterator it = behaviors_.begin();
	for (; it != behaviors_.end(); ++it)
		(*it)->deactivate();
}
//----------------------------------------------------------------------------//
