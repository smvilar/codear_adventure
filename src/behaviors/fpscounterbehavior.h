#ifndef FORAGERS_FPSCOUNTERBEHAVIOR_H
#define FORAGERS_FPSCOUNTERBEHAVIOR_H
//----------------------------------------------------------------------------//
#include "DllExport.h"
#include "gameobject/behavior.h"
#include "util/FPSCounter.h"
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
	FPSCounter _fpsCounter;
};
//----------------------------------------------------------------------------//
} // end namespace he
//----------------------------------------------------------------------------//
#endif // FORAGERS_FPSCOUNTERBEHAVIOR_H
