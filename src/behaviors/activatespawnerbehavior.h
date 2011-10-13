#ifndef HE_ACTIVATESPAWNERBEHAVIOR_H
#define HE_ACTIVATESPAWNERBEHAVIOR_H
//----------------------------------------------------------------------------//
#include "DllExport.h"
#include "gameobject/behavior.h"
//----------------------------------------------------------------------------//
namespace he {
//----------------------------------------------------------------------------//
class ENGINE_API ActivateSpawnerBehavior : public Behavior
{
public:
	virtual void activate();
	virtual Behavior* clone() const;
};
//----------------------------------------------------------------------------//
} // end namespace he
//----------------------------------------------------------------------------//
#endif // HE_ACTIVATESPAWNERBEHAVIOR_H
