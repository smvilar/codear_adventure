#include "behaviors/fpscounterbehavior.h"
#include <iostream>
//----------------------------------------------------------------------------//
using namespace foragers;
//----------------------------------------------------------------------------//
void FPSCounterBehavior::update()
{
	_fpsCounter.tick();

	std::cout << "FPS: " << _fpsCounter.getFPS() << std::endl;
}
//----------------------------------------------------------------------------//
Behavior* FPSCounterBehavior::clone() const
{
	return new FPSCounterBehavior;
}
//----------------------------------------------------------------------------//
