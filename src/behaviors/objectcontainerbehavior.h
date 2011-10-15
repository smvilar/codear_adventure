#ifndef HE_OBJECTCONTAINERBEHAVIOR_H
#define HE_OBJECTCONTAINERBEHAVIOR_H
//----------------------------------------------------------------------------//
#include "DllExport.h"
#include "gameobject/behavior.h"
//----------------------------------------------------------------------------//
namespace he {
//----------------------------------------------------------------------------//
class ENGINE_API ObjectContainerBehavior : public Behavior
{
public:
	virtual void added();

	virtual Behavior* clone() const;
};
//----------------------------------------------------------------------------//
} // end namespace he
//----------------------------------------------------------------------------//
#endif // HE_OBJECTCONTAINERBEHAVIOR_H
