#ifndef HE_OBJECTREGISTRYBEHAVIOR_H
#define HE_OBJECTREGISTRYBEHAVIOR_H
//----------------------------------------------------------------------------//
#include "dllexport.h"
#include "gameobject/behavior.h"
//----------------------------------------------------------------------------//
namespace he {
//----------------------------------------------------------------------------//
class ENGINE_API ObjectRegistryBehavior : public Behavior
{
public:
	Behavior* clone() const { return new ObjectRegistryBehavior; }

private:
	void activate();
};
//----------------------------------------------------------------------------//
} // end namespace he
//----------------------------------------------------------------------------//
#endif // HE_OBJECTREGISTRYBEHAVIOR_H
