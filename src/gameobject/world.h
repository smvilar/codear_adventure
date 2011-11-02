#ifndef HE_WORLD_H
#define HE_WORLD_H
//----------------------------------------------------------------------------//
#include <vector>
#include <map>
#include <string>
#include <queue>
//----------------------------------------------------------------------------//
#include "dllexport.h"
#include "core/scene.h"
#include "resource/resourcemanager.h"
#include "gameobject/worldserializer.h"
//----------------------------------------------------------------------------//
namespace he {
//----------------------------------------------------------------------------//
class GameObject;
class Behavior;
class Message;
//----------------------------------------------------------------------------//
// World
//
// Class that manages and constructs GameObject objects
//----------------------------------------------------------------------------//
class ENGINE_API World
{
public:
	World();
	~World();

/// GameObject Management
public:
	// Adds a GameObject to the list of objects in the world
	void addObject(GameObject *object);
	// Removes a GameObject from the list of objects in the world
	void removeObject(GameObject *object);
	// Removes a GameObject from the list of objects in the world
	void removeObject(const std::string &name);
	// Gets a GameObject by its name, returns 0 if not found
	GameObject* getObject(const std::string &name);

	void removeAllObjects();

	// Updates all the objects in the world
	void update();
	// Sends a message to every object in the world
	void broadcast(const Message &message);

/// GameObject Prototypes
public:
	// Registers a GameObject as a prototype to create more objects like it
	void registerObjectPrototype(const std::string &name, GameObject *object);
	// Unregisters a GameObject as a prototype
	void unregisterObjectPrototype(const std::string &name);
	// Creates a GameObject from a prototype
	GameObject* createObject(const std::string &name) const;

	void cleanRegisteredObjectPrototypes();

/// GameObject Behavior Management
public:
	// Registers a behavior in a list so it can be recognized later when constructing a new object
	void registerBehavior(const std::string &name, Behavior *behavior);
	// Unregisters a behavior
	void unregisterBehavior(const std::string &name);
	// Returns a copy of a registered behavior
	Behavior* createBehavior(const std::string &name) const;

	void cleanRegisteredBehaviors();

/// GameObject Parsing
public:
	// Creates an object from a json file
	GameObject* parseObject(const std::string &filename);

/// Persistence
public:
	// Saves the state of the world in a json file
	void saveState(const std::string &filename) const;
	// Loads the state of the world from a json file
	void loadState(const std::string &filename);

	WorldSerializer& getWorldSerializer();

private:
	WorldSerializer worldSerializer_;

/// Type definitions
private:
	typedef std::vector<GameObject*> ObjectVector;
	typedef std::map<std::string, GameObject*> ObjectMap;
	typedef std::map<std::string, Behavior*> BehaviorMap;

/// Data
private:
	ObjectVector objects_;
	ObjectMap objectPrototypes_;
	BehaviorMap behaviors_;

/// Queues
private:
	std::queue<GameObject*> objectsToAdd_;
	std::queue<GameObject*> objectsToRemove_;

	void processQueues();
	void doAddObject(GameObject *object);
	void doRemoveObject(GameObject *object);

/// Scene (for behaviors that need to render stuff)
public:
	Scene& getScene();
private:
	Scene scene_;

/// ResourceManager
public:
	ResourceManager& getResourceManager();
private:
	ResourceManager resourceManager_;

private:
	friend class WorldSerializer;
};
//----------------------------------------------------------------------------//
#include "world.inl"
//----------------------------------------------------------------------------//
} // end namespace he
//----------------------------------------------------------------------------//
#endif // HE_WORLD_H
