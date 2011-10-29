#ifndef HE_FPSCOUNTERBEHAVIOR_H
#define HE_FPSCOUNTERBEHAVIOR_H
//----------------------------------------------------------------------------//
#include "dllexport.h"
#include "gameobject/behavior.h"
#include "util/fpscounter.h"
//----------------------------------------------------------------------------//
namespace he {
//----------------------------------------------------------------------------//
class ENGINE_API FPSCounterBehavior : public Behavior
{
public:
	virtual void update();
	virtual Behavior* clone() const;

private:
	virtual void added();
	virtual void removed();

private:
	FPSCounter fpsCounter_;
};
//----------------------------------------------------------------------------//
} // end namespace he
//----------------------------------------------------------------------------//
#endif // HE_FPSCOUNTERBEHAVIOR_H
