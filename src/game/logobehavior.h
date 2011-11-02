#ifndef HE_LOGOBEHAVIOR_H
#define HE_LOGOBEHAVIOR_H
//----------------------------------------------------------------------------//
#include <hierophantengine.h>
//----------------------------------------------------------------------------//
using namespace he;
//----------------------------------------------------------------------------//
class FPSCounter;
class ScreenDirector;
//----------------------------------------------------------------------------//
class LogoBehavior : public Behavior
{
public:
	Behavior* clone() const { return new LogoBehavior; }
	void update();

private:
	void activate();

	u32 logoTime_;
	sf::Clock clock_;
};
//----------------------------------------------------------------------------//
#endif // HE_LOGOBEHAVIOR_H
