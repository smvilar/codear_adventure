#include "gameobject/world.h"
//----------------------------------------------------------------------------//
#include <algorithm>
#include <fstream>
//----------------------------------------------------------------------------//
#include "core/assert.h"
#include "gameobject/gameobject.h"
#include "gameobject/attribute.h"
#include "gameobject/behavior.h"
#include "gameobject/objectparser.h"
#include "gameobject/worldserializer.h"
#include "gameobject/message.h"
#include "behaviors/behaviors.h"
//----------------------------------------------------------------------------//
using namespace he;
//----------------------------------------------------------------------------//
// Helper class that acts like a "Functor"
//----------------------------------------------------------------------------//
class ObjectNamesAreEqual
{
	const std::string &name_;
public:
	ObjectNamesAreEqual(const std::string &name) : name_(name) {}
	bool operator()(GameObject* obj)
	{
		return obj->name == name_;
	}
};
//----------------------------------------------------------------------------//
World::World()
{
	Behaviors::registerToWorld(*this);
}
//----------------------------------------------------------------------------//
World::~World()
{
	processQueues();
	removeAllObjects();
	cleanRegisteredObjectPrototypes();
	cleanRegisteredBehaviors();
}
//----------------------------------------------------------------------------//
void World::addObject(GameObject *object)
{
	objectsToAdd_.push(object);
}
//----------------------------------------------------------------------------//
void World::removeObject(GameObject *object)
{
	objectsToRemove_.push(object);
}
//----------------------------------------------------------------------------//
GameObject* World::getObject(const std::string &name)
{
	ObjectVector::iterator it =
		std::find_if(objects_.begin(), objects_.end(), ObjectNamesAreEqual(name));
	return (it != objects_.end()) ? *it : 0;
}
//----------------------------------------------------------------------------//
void World::removeAllObjects()
{
	ObjectVector::iterator it = objects_.begin();
	for (; it != objects_.end(); ++it)
		delete *it;
}
//----------------------------------------------------------------------------//
void World::update()
{
	ObjectVector::iterator it = objects_.begin();
	for (; it != objects_.end(); ++it)
		(*it)->update();
	processQueues();
}
//----------------------------------------------------------------------------//
void World::broadcast(const Message &message)
{
	ObjectVector::iterator it = objects_.begin();
	for (; it != objects_.end(); ++it)
	{
		(*it)->broadcast(message);
	}
}
//----------------------------------------------------------------------------//
void World::registerObjectPrototype(const std::string &name, GameObject *object)
{
	Assert(objectPrototypes_.find(name) == objectPrototypes_.end(),
		   "Registering a duplicate object");

	objectPrototypes_[name] = object;
}
//----------------------------------------------------------------------------//
void World::unregisterObjectPrototype(const std::string &name)
{
	Assert(objectPrototypes_.find(name) != objectPrototypes_.end(),
		   "Unregistering an unexistent object prototype");

	delete objectPrototypes_[name];
	objectPrototypes_.erase(name);
}
//----------------------------------------------------------------------------//
GameObject* World::createObject(const std::string &name) const
{
	ObjectMap::const_iterator it = objectPrototypes_.find(name);
	Assert(it != objectPrototypes_.end(), "Couldn't find object prototype");

	return it->second->clone();
}
//----------------------------------------------------------------------------//
void World::cleanRegisteredObjectPrototypes()
{
	ObjectMap::iterator it = objectPrototypes_.begin();
	for (; it != objectPrototypes_.end(); ++it)
		delete it->second;
}
//----------------------------------------------------------------------------//
void World::registerBehavior(const std::string &name, Behavior *behavior)
{
	Assert(behaviors_.find(name) == behaviors_.end(),
		   "Registering a duplicate behavior");

	behavior->pWorld_ = this;
	behaviors_[name] = behavior;
}
//----------------------------------------------------------------------------//
void World::unregisterBehavior(const std::string &name)
{
	Assert(behaviors_.find(name) != behaviors_.end(),
		   "Unregistering an unexistent behavior");

	delete behaviors_[name];
	behaviors_.erase(name);
}
//----------------------------------------------------------------------------//
Behavior* World::createBehavior(const std::string &name) const
{
	BehaviorMap::const_iterator it = behaviors_.find(name);
	if (it != behaviors_.end())
	{
		Behavior* behavior = it->second->clone();
		behavior->pWorld_ = const_cast<World*>(this);
		return behavior;
	}
	else return 0;
}
//----------------------------------------------------------------------------//
void World::cleanRegisteredBehaviors()
{
	BehaviorMap::iterator it = behaviors_.begin();
	for (; it != behaviors_.end(); ++it)
		delete it->second;
}
//----------------------------------------------------------------------------//
GameObject* World::parseObject(const std::string &filename)
{
	GameObject* obj = new GameObject("unnamed");
	ObjectParser parser;
	parser.parse(resourceManager_.getTextResource(filename),
				 *obj, this);
	return obj;
}
//----------------------------------------------------------------------------//
void World::saveState(const std::string &filename) const
{
	std::ofstream ofs(filename.c_str());
	worldSerializer_.serialize(*this, ofs);
}
//----------------------------------------------------------------------------//
void World::loadState(const std::string &filename)
{
	worldSerializer_.deserialize(*this, resourceManager_.getTextResource(filename));
}
//----------------------------------------------------------------------------//
WorldSerializer& World::getWorldSerializer()
{
	return worldSerializer_;
}
//----------------------------------------------------------------------------//
void World::processQueues()
{
	while (!objectsToAdd_.empty())
	{
		doAddObject(objectsToAdd_.front());
		objectsToAdd_.pop();
	}

	while (!objectsToRemove_.empty())
	{
		doRemoveObject(objectsToRemove_.front());
		objectsToRemove_.pop();
	}
}
//----------------------------------------------------------------------------//
void World::doAddObject(GameObject *object)
{
	Assert(object, "Object to add shouldn't be null");
	objects_.push_back(object);
	object->pWorld_ = this;
	object->added();
}
//----------------------------------------------------------------------------//
void World::doRemoveObject(GameObject *object)
{
	Assert(object, "Object to remove shouldn't be null");
	ObjectVector::iterator it =
			std::find(objects_.begin(), objects_.end(), object);
	Assert(it != objects_.end(), "Object to remove should be in the list");
	objects_.erase(it);
	object->removed();
	delete object;
	object = 0;
}
//----------------------------------------------------------------------------//
