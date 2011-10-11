#ifndef FORAGERS_GAMEOBJECT_H
#define FORAGERS_GAMEOBJECT_H
//----------------------------------------------------------------------------//
#include <string>
#include <vector>
#include <map>
//----------------------------------------------------------------------------//
#include "DllExport.h"
#include "gameobject/attribute.h"
//----------------------------------------------------------------------------//
namespace foragers
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
	GameObject(const char* name);

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
	void broadcast(const char* message, void* args = 0);

	void removeFromWorld();

	GameObject* clone() const;

private:
	void added();
	void removed();

private:
	World* _pWorld;

private:
	typedef std::vector<Behavior*> BehaviorVector;
	BehaviorVector _behaviors;

	typedef std::map<std::string, Attribute*> AttributeMap;
	AttributeMap _attributes;

	friend class World;
};
//----------------------------------------------------------------------------//
} // end namespace foragers
//----------------------------------------------------------------------------//
#endif // FORAGERS_GAMEOBJECT_H
