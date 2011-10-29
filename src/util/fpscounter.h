#ifndef HE_FPSCOUNTER_H
#define HE_FPSCOUNTER_H
//----------------------------------------------------------------------------//
#include <string>
#include "dllexport.h"
#include "core/types.h"
//----------------------------------------------------------------------------//
namespace he
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
#include "fpscounter.inl"
//----------------------------------------------------------------------------//
} // end namespace he
//----------------------------------------------------------------------------//
#endif // HE_FPSCOUNTER_H
//----------------------------------------------------------------------------//
