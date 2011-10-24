#ifndef HE_OBJECTCONTAINERBEHAVIOR_H
#define HE_OBJECTCONTAINERBEHAVIOR_H
//----------------------------------------------------------------------------//
#include "dllexport.h"
#include "gameobject/behavior.h"
//----------------------------------------------------------------------------//
namespace he {
//----------------------------------------------------------------------------//
class ENGINE_API ObjectContainerBehavior : public Behavior
{
public:
	virtual Behavior* clone() const;

private:
	virtual void added();
	virtual void activate();
};
//----------------------------------------------------------------------------//
} // end namespace he
//----------------------------------------------------------------------------//
#endif // HE_OBJECTCONTAINERBEHAVIOR_H
