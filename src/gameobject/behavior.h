#ifndef FORAGERS_GOBEHAVIOR_H
#define FORAGERS_GOBEHAVIOR_H
//----------------------------------------------------------------------------//
#include "DllExport.h"
//----------------------------------------------------------------------------//
namespace he
{
//----------------------------------------------------------------------------//
class GameObject;
class World;
//----------------------------------------------------------------------------//
class ENGINE_API Behavior
{
public:
	Behavior();
	virtual ~Behavior() {}

	virtual void update() {}
	virtual void handleMessage(const char */*message*/, void */*args*/) {}

	virtual Behavior* clone() const = 0;

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
} // end namespace he
//----------------------------------------------------------------------------//
#endif // FORAGERS_GOBEHAVIOR_H
