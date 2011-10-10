#include "gameobject/goworld.h"
//----------------------------------------------------------------------------//
#include <algorithm>
//----------------------------------------------------------------------------//
#include "core/Assert.h"
#include "gameobject/gameobject.h"
#include "gameobject/goattribute.h"
#include "gameobject/gobehavior.h"
#include "gameobject/objectparser.h"
//----------------------------------------------------------------------------//
using namespace foragers;
//----------------------------------------------------------------------------//
class ObjectNamesAreEqual
{
	const char* _name;
public:
	ObjectNamesAreEqual(const char* name) : _name(name) {}
	bool operator()(GameObject* obj)
	{
		return (obj->name.compare(_name) == 0);
	}
};
//----------------------------------------------------------------------------//
World::World()
: _scene(0)
{
	// ...
}
//----------------------------------------------------------------------------//
void World::addObject(GameObject *object)
{
	_objects.push_back(object);
	object->_pWorld = this;
	object->added();
}
//----------------------------------------------------------------------------//
void World::removeObject(GameObject *object)
{
	std::remove(_objects.begin(), _objects.end(), object);
	object->removed();
	object->_pWorld = 0;
}
//----------------------------------------------------------------------------//
GameObject* World::getObject(const char* name)
{
	ObjectVector::iterator it = std::find_if(_objects.begin(), _objects.end(),
											 ObjectNamesAreEqual(name));
	return (it != _objects.end()) ? *it : 0;
}
//----------------------------------------------------------------------------//
void World::registerObjectPrototype(const char *name, GameObject *object)
{
	Assert(_objectPrototypes.find(name) == _objectPrototypes.end(),
		   "Registering a duplicate object");

	_objectPrototypes[name] = object;
}
//----------------------------------------------------------------------------//
void World::unregisterObjectPrototype(const char *name)
{
	_objectPrototypes.erase(name);
}
//----------------------------------------------------------------------------//
GameObject* World::createObject(const char *name) const
{
	ObjectMap::const_iterator it = _objectPrototypes.find(name);
	Assert(it != _objectPrototypes.end(), "Couldn't find object prototype");

	return it->second->clone();
}
//----------------------------------------------------------------------------//
void World::registerBehavior(const char *name, Behavior *behavior)
{
	Assert(_behaviors.find(name) == _behaviors.end(),
		   "Registering a duplicate behavior");

	behavior->_pWorld = this;
	_behaviors[name] = behavior;
}
//----------------------------------------------------------------------------//
void World::unregisterBehavior(const char *name)
{
	Assert(_behaviors.find(name) != _behaviors.end(),
		   "Unregistering an unexistent behavior");

	_behaviors[name]->_pWorld = 0;
	_behaviors.erase(name);
}
//----------------------------------------------------------------------------//
Behavior* World::createBehavior(const char *name) const
{
	BehaviorMap::const_iterator it = _behaviors.find(name);
	if (it != _behaviors.end())
	{
		Behavior* behavior = it->second->clone();
		behavior->_pWorld = const_cast<World*>(this);
		return behavior;
	}
	else return 0;
}
//----------------------------------------------------------------------------//
void World::update()
{
	ObjectVector::iterator it = _objects.begin();
	for (; it != _objects.end(); ++it)
	{
		(*it)->update();
	}
}
//----------------------------------------------------------------------------//
void World::broadcast(const char *message, void *args)
{
	ObjectVector::iterator it = _objects.begin();
	for (; it != _objects.end(); ++it)
	{
		(*it)->broadcast(message, args);
	}
}
//----------------------------------------------------------------------------//
GameObject* World::parseObject(const char *filename)
{
	GameObject* obj = new GameObject("unnamed");
	ObjectParser parser;
	parser.parse(filename, *obj, this);
	return obj;
}
//----------------------------------------------------------------------------//
