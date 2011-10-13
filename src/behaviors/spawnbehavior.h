#ifndef HE_SPAWNBEHAVIOR_H
#define HE_SPAWNBEHAVIOR_H
//----------------------------------------------------------------------------//
#include "DllExport.h"
#include "gameobject/behavior.h"
//----------------------------------------------------------------------------//
namespace he {
//----------------------------------------------------------------------------//
class ENGINE_API SpawnBehavior : public Behavior
{
public:
	virtual Behavior* clone() const;

	virtual void activate();
};
//----------------------------------------------------------------------------//
} // end namespace he
//----------------------------------------------------------------------------//
#endif // HE_SPAWNBEHAVIOR_H
