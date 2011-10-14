#ifndef HE_WORLD_H
#define HE_WORLD_H
//----------------------------------------------------------------------------//
#include <vector>
#include <map>
#include <string>
//----------------------------------------------------------------------------//
#include "DllExport.h"
#include "resource/ResourceManager.h"
#include "core/Scene.h"
//----------------------------------------------------------------------------//
namespace he {
//----------------------------------------------------------------------------//
class GameObject;
class Behavior;
//----------------------------------------------------------------------------//
// World
//
// Class that manages and constructs GameObject objects
//----------------------------------------------------------------------------//
class ENGINE_API World
{
public:
	~World();

/// GameObject Management
public:
	// Adds a GameObject to the list of objects in the world
	void addObject(GameObject *object);
	// Removes a GameObject from the list of objects in the world
	void removeObject(GameObject *object);
	// Gets a GameObject by its name, returns 0 if not found
	GameObject* getObject(const char* name);

	// Updates all the objects in the world
	void update();
	// Sends a message to every object in the world
	void broadcast(const char* message, void* args);

/// GameObject Prototypes
public:
	// Registers a GameObject as a prototype to create more objects like it
	void registerObjectPrototype(const char* name, GameObject* object);
	// Unregisters a GameObject as a prototype
	void unregisterObjectPrototype(const char* name);
	// Creates a GameObject from a prototype
	GameObject* createObject(const char* name) const;

/// GameObject Behavior Management
public:
	// Registers a behavior in a list so it can be recognized later when constructing a new object
	void registerBehavior(const char* name, Behavior* behavior);
	// Unregisters a behavior
	void unregisterBehavior(const char* name);
	// Returns a copy of a registered behavior
	Behavior* createBehavior(const char* name) const;

/// GameObject Parsing
public:
	// Creates an object from a json file
	GameObject* parseObject(const char* filename);
	
/// Type definitions
public:
	typedef std::vector<GameObject*> ObjectVector;
	typedef std::map<std::string, GameObject*> ObjectMap;
	typedef std::map<std::string, Behavior*> BehaviorMap;

private:
	ObjectVector _objects;
	ObjectMap _objectPrototypes;
	BehaviorMap _behaviors;

/// Scene and ResourceManager (for behaviors that need to render stuff)
public:
	Scene& getScene();
	ResourceManager& getResourceManager();

private:
	Scene _scene;
	ResourceManager _resourceManager;
};
//----------------------------------------------------------------------------//
#include "world.inl"
//----------------------------------------------------------------------------//
} // end namespace he
//----------------------------------------------------------------------------//
#endif // HE_WORLD_H
