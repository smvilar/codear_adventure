#ifndef HE_GAMEOBJECT_H
#define HE_GAMEOBJECT_H
//----------------------------------------------------------------------------//
#include <string>
#include <vector>
#include <map>
#include <queue>
//----------------------------------------------------------------------------//
#include "dllexport.h"
#include "gameobject/attribute.h"
#include "gameobject/message.h"
//----------------------------------------------------------------------------//
namespace he
{
//----------------------------------------------------------------------------//
class Behavior;
class World;
//----------------------------------------------------------------------------//
class ENGINE_API GameObject
{
public:
	std::string name;

public:
	GameObject(const std::string &name);
	~GameObject();

	std::string debugToString() const;

/// Attributes
public:
	void addAttribute(const std::string &name, Attribute *attribute);
	void removeAttribute(const std::string &name);
	Attribute* getAttribute(const std::string &name);

	template <typename T>
	T getAttributeAs(const char *name)
	{
		return getAttribute(name)->get<T>();
	}

	Attribute* operator[](const std::string &attributeName) { return getAttribute(attributeName); }

/// Behaviors
public:
	void addBehavior(Behavior *behavior);
	void removeBehavior(Behavior *behavior);
	Behavior* getBehaviorByName(const std::string &name);
	void removeBehaviorByName(const std::string &name)
	{
		removeBehavior(getBehaviorByName(name));
	}

/// Logic stuff
public:
	void update();
	void broadcast(const Message &message);

	void removeFromWorld();

	GameObject* clone() const;

private:
	void added();
	void removed();

private:
	World *pWorld_;

private:
	typedef std::vector<Behavior*> BehaviorVector;
	BehaviorVector behaviors_;

	typedef std::map<std::string, Attribute*> AttributeMap;
	AttributeMap attributes_;

private:
	std::queue<Behavior*> behaviorsToAdd_;
	std::queue<Behavior*> behaviorsToRemove_;
	std::queue<Message> messages_;

	void processQueues();
	void doAddBehavior(Behavior *behavior);
	void doRemoveBehavior(Behavior *behavior);
	void doBroadcast(const Message &message);

private:
	friend class ObjectParser;
	friend class World;
	friend class WorldSerializer;
};
//----------------------------------------------------------------------------//
} // end namespace he
//----------------------------------------------------------------------------//
#endif // HE_GAMEOBJECT_H
