#ifndef FORAGERS_GAMEOBJECT_H
#define FORAGERS_GAMEOBJECT_H
//----------------------------------------------------------------------------//
#include <string>
#include <vector>
#include <map>
//----------------------------------------------------------------------------//
#include "DllExport.h"
#include "gameobject/goattribute.h"
//----------------------------------------------------------------------------//
namespace foragers
{
//----------------------------------------------------------------------------//
class GOBehavior;
class World;
//----------------------------------------------------------------------------//
class ENGINE_API GameObject
{
public:
	std::string name;

public:
	GameObject(const char* name);

	void addBehavior(GOBehavior* behavior);
	void removeBehavior(GOBehavior* behavior);

	void addAttribute(const char* name, GOAttribute* attribute);
	void removeAttribute(const char* name);
	GOAttribute* getAttribute(const char* name);

	template <typename T>
	T getAttributeAs(const char* name)
	{
		return getAttribute(name)->getValue<T>();
	}

	void update();
	void broadcast(const char* message, void* args);

	GameObject* clone() const;

private:
	void added();
	void removed();

	World* _pWorld;

private:
	typedef std::vector<GOBehavior*> BehaviorVector;
	BehaviorVector _behaviors;

	typedef std::map<std::string, GOAttribute*> AttributeMap;
	AttributeMap _attributes;

	friend class World;
};
//----------------------------------------------------------------------------//
} // end namespace foragers
//----------------------------------------------------------------------------//
#endif // FORAGERS_GAMEOBJECT_H
