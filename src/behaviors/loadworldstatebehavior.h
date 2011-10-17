#ifndef HE_LOADWORLDSTATEBEHAVIOR_H
#define HE_LOADWORLDSTATEBEHAVIOR_H
//----------------------------------------------------------------------------//
#include "DllExport.h"
#include "gameobject/behavior.h"
//----------------------------------------------------------------------------//
namespace he {
//----------------------------------------------------------------------------//
class ENGINE_API LoadWorldStateBehavior : public Behavior
{
public:
	virtual Behavior* clone() const;

private:
	virtual void activate();
};
//----------------------------------------------------------------------------//
} // end namespace he
//----------------------------------------------------------------------------//
#endif // HE_LOADWORLDSTATEBEHAVIOR_H
