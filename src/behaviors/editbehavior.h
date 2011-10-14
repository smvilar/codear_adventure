#ifndef HE_EDITBEHAVIOR_H
#define HE_EDITBEHAVIOR_H
//----------------------------------------------------------------------------//
#include <vector>
//----------------------------------------------------------------------------//
#include "DllExport.h"
#include "gameobject/behavior.h"
//----------------------------------------------------------------------------//
namespace he {
//----------------------------------------------------------------------------//
class GameObject;
//----------------------------------------------------------------------------//
class ENGINE_API EditBehavior : public Behavior
{
public:
	virtual Behavior* clone() const;

private:
	virtual void activate();

private:
	std::vector<GameObject*> _objects;
};
//----------------------------------------------------------------------------//
} // end namespace he
//----------------------------------------------------------------------------//
#endif // HE_EDITBEHAVIOR_H
