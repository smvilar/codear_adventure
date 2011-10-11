#ifndef FORAGERS_FPSCOUNTERBEHAVIOR_H
#define FORAGERS_FPSCOUNTERBEHAVIOR_H
//----------------------------------------------------------------------------//
#include "DllExport.h"
#include "gameobject/gobehavior.h"
#include "util/FPSCounter.h"
//----------------------------------------------------------------------------//
namespace foragers {
//----------------------------------------------------------------------------//
class ENGINE_API FPSCounterBehavior : public Behavior
{
public:
	virtual void update();
	virtual Behavior* clone() const;

private:
	FPSCounter _fpsCounter;
};
//----------------------------------------------------------------------------//
} // end namespace foragers
//----------------------------------------------------------------------------//
#endif // FORAGERS_FPSCOUNTERBEHAVIOR_H
