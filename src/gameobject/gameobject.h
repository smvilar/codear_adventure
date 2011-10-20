#ifndef HE_GAMEOBJECT_H
#define HE_GAMEOBJECT_H
//----------------------------------------------------------------------------//
#include <string>
#include <vector>
#include <map>
//----------------------------------------------------------------------------//
#include "DllExport.h"
#include "gameobject/attribute.h"
//----------------------------------------------------------------------------//
namespace he
{
//----------------------------------------------------------------------------//
class Behavior;
class World;
class Message;
//----------------------------------------------------------------------------//
class ENGINE_API GameObject
{
public:
	std::string name;

public:
	GameObject(const char* name);
	~GameObject();

	void addBehavior(Behavior* behavior);
	void removeBehavior(Behavior* behavior);

	void addAttribute(const char* name, Attribute* attribute);
	void removeAttribute(const char* name);
	Attribute* getAttribute(const char* name);

	template <typename T>
	T getAttributeAs(const char* name)
	{
		return getAttribute(name)->getValue<T>();
	}

	void update();
	void broadcast(const Message &message);

	void removeFromWorld();

	GameObject* clone() const;

private:
	void added();
	void removed();

private:
	World* pWorld_;

private:
	typedef std::vector<Behavior*> BehaviorVector;
	BehaviorVector behaviors_;

	typedef std::map<std::string, Attribute*> AttributeMap;
	AttributeMap attributes_;

	friend class World;
	friend class WorldSerializer;
};
//----------------------------------------------------------------------------//
} // end namespace he
//----------------------------------------------------------------------------//
#endif // HE_GAMEOBJECT_H
