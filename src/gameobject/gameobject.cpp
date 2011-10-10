#include "gameobject/gameobject.h"
//----------------------------------------------------------------------------//
#include "gameobject/goattribute.h"
#include "gameobject/gobehavior.h"
#include "core/Assert.h"
//----------------------------------------------------------------------------//
using namespace foragers;
//----------------------------------------------------------------------------//
GameObject::GameObject(const char *name)
: name(name)
{
}
//----------------------------------------------------------------------------//
void GameObject::addBehavior(GOBehavior *behavior)
{
	_behaviors.push_back(behavior);
	behavior->_pOwner = this;
	behavior->added();
}
//----------------------------------------------------------------------------//
void GameObject::removeBehavior(GOBehavior *behavior)
{
	behavior->removed();
	behavior->_pOwner = 0;
	std::remove(_behaviors.begin(), _behaviors.end(), behavior);
}
//----------------------------------------------------------------------------//
void GameObject::addAttribute(const char *name, GOAttribute *attribute)
{
	Assert(_attributes.find(name) == _attributes.end(),
		   "Error when adding attribute: another one with the same name exists");
	_attributes[name] = attribute;
}
//----------------------------------------------------------------------------//
void GameObject::removeAttribute(const char *name)
{
	_attributes.erase(name);
}
//----------------------------------------------------------------------------//
GOAttribute* GameObject::getAttribute(const char *name)
{
	AttributeMap::iterator it = _attributes.find(name);
	return it != _attributes.end() ? it->second : 0;
}
//----------------------------------------------------------------------------//
void GameObject::update()
{
	BehaviorVector::iterator it = _behaviors.begin();
	for (; it != _behaviors.end(); ++it)
		(*it)->update();
}
//----------------------------------------------------------------------------//
void GameObject::broadcast(const char *message, void *args)
{
	BehaviorVector::iterator it = _behaviors.begin();
	for (; it != _behaviors.end(); ++it)
		(*it)->handleMessage(message, args);
}
//----------------------------------------------------------------------------//
GameObject* GameObject::clone() const
{
	GameObject* copy = new GameObject(name.c_str());

	// clone behaviors
	BehaviorVector::const_iterator itBehavior = _behaviors.begin();
	for (; itBehavior != _behaviors.end(); ++itBehavior)
	{
		copy->addBehavior((*itBehavior)->clone());
	}

	// clone attributes
	AttributeMap::const_iterator itAttribute = _attributes.begin();
	for (; itAttribute != _attributes.end(); ++itAttribute)
	{
		copy->addAttribute(itAttribute->first.c_str(), itAttribute->second);
	}

	return copy;
}
//----------------------------------------------------------------------------//
void GameObject::added()
{
	BehaviorVector::iterator it = _behaviors.begin();
	for (; it != _behaviors.end(); ++it)
		(*it)->activate();
}
//----------------------------------------------------------------------------//
void GameObject::removed()
{
	BehaviorVector::iterator it = _behaviors.begin();
	for (; it != _behaviors.end(); ++it)
		(*it)->deactivate();
}
//----------------------------------------------------------------------------//
