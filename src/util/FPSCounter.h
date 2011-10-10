#ifndef FORAGERS_FPSCOUNTER_H
#define FORAGERS_FPSCOUNTER_H
//----------------------------------------------------------------------------//
#include <string>
#include "DllExport.h"
#include "core/Types.h"
//----------------------------------------------------------------------------//
namespace foragers
{
//----------------------------------------------------------------------------//
class ENGINE_API FPSCounter
{
public:
	FPSCounter(u32 maxFramerate = 0);

	void tick();

	u32 getFPS() const;
	u32 getDT() const;

	void setMaxFramerate(u32 maxFramerate);
	u32 getMaxFramerate() const;

private:
	u32 _fps;
	u32 _dt;
	u32 _maxFramerate;

	u32 _lastFrameTime;
	u32 _lastSecondTime;
	u32 _frameCount;
};
//----------------------------------------------------------------------------//
#include "FPSCounter.inl"
//----------------------------------------------------------------------------//
} // end namespace foragers
//----------------------------------------------------------------------------//
#endif // FORAGERS_FPSCOUNTER_H
//----------------------------------------------------------------------------//
