#ifndef FORAGERS_GAMEOBJECT_H
#define FORAGERS_GAMEOBJECT_H
//----------------------------------------------------------------------------//
#include <string>
#include <vector>
#include <map>
#include "DllExport.h"
//----------------------------------------------------------------------------//
namespace foragers
{
//----------------------------------------------------------------------------//
class GOBehavior;
class GOAttribute;
class GOWorld;
//----------------------------------------------------------------------------//
class ENGINE_API GameObject
{
public:
	std::string name;

	GameObject(const char* name);

	void addBehavior(GOBehavior* behavior);
	void removeBehavior(GOBehavior* behavior);

	void addAttribute(const char* name, GOAttribute* attribute);
	void removeAttribute(const char* name);
	GOAttribute* getAttribute(const char* name);

	void update();
	void broadcast(const char* message, void* args);

	GameObject* clone() const;

private:
	void added();
	void removed();

	GOWorld* _pWorld;

private:
	typedef std::vector<GOBehavior*> BehaviorVector;
	BehaviorVector _behaviors;

	typedef std::map<std::string, GOAttribute*> AttributeMap;
	AttributeMap _attributes;

	friend class GOWorld;
};
//----------------------------------------------------------------------------//
} // end namespace foragers
//----------------------------------------------------------------------------//
#endif // FORAGERS_GAMEOBJECT_H
