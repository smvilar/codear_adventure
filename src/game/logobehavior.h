#ifndef HE_LOGOBEHAVIOR_H
#define HE_LOGOBEHAVIOR_H
//----------------------------------------------------------------------------//
#include "gameobject/behavior.h"
//----------------------------------------------------------------------------//
namespace he {
class FPSCounter;
class ScreenDirector;
} // end namespace he
//----------------------------------------------------------------------------//
class LogoBehavior : public he::Behavior
{
public:
	virtual he::Behavior* clone() const { return new LogoBehavior; }
	virtual void update();

private:
	virtual void activate();

	int logoTime_;
	int timer_;
	he::FPSCounter *fpsCounter_;
};
//----------------------------------------------------------------------------//
#endif // HE_LOGOBEHAVIOR_H
