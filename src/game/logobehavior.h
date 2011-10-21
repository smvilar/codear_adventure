#ifndef HE_LOGOBEHAVIOR_H
#define HE_LOGOBEHAVIOR_H
//----------------------------------------------------------------------------//
#include "DllExport.h"
#include "gameobject/behavior.h"
//----------------------------------------------------------------------------//
namespace he {
//----------------------------------------------------------------------------//
class FPSCounter;
class ScreenDirector;
//----------------------------------------------------------------------------//
class ENGINE_API LogoBehavior : public Behavior
{
public:
	virtual Behavior* clone() const { return new LogoBehavior; }
	virtual void update();

private:
	virtual void activate();

	int logoTime_;
	int timer_;
	FPSCounter *fpsCounter_;
};
//----------------------------------------------------------------------------//
} // end namespace he
//----------------------------------------------------------------------------//
#endif // HE_LOGOBEHAVIOR_H
