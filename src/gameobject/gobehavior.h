#ifndef FORAGERS_GOBEHAVIOR_H
#define FORAGERS_GOBEHAVIOR_H
//----------------------------------------------------------------------------//
#include "DllExport.h"
//----------------------------------------------------------------------------//
namespace foragers
{
//----------------------------------------------------------------------------//
class GameObject;
class World;
//----------------------------------------------------------------------------//
class ENGINE_API GOBehavior
{
public:
	GOBehavior();
	virtual ~GOBehavior() {}

	virtual void update() {}
	virtual void handleMessage(const char */*message*/, void */*args*/) {}

	virtual GOBehavior* clone() const = 0;

protected:
	virtual void added() {}
	virtual void removed() {}
	virtual void activate() {}
	virtual void deactivate() {}

protected:
	GameObject *_pOwner;
	World *_pWorld;

	friend class GameObject;
	friend class World;
};
//----------------------------------------------------------------------------//
} // end namespace foragers
//----------------------------------------------------------------------------//
#endif // FORAGERS_GOBEHAVIOR_H
