#include "behaviors/fpscounterbehavior.h"
//----------------------------------------------------------------------------//
#include "gameobject/gameobject.h"
//----------------------------------------------------------------------------//
using namespace he;
//----------------------------------------------------------------------------//
void FPSCounterBehavior::update()
{
	_fpsCounter.tick();
}
//----------------------------------------------------------------------------//
Behavior* FPSCounterBehavior::clone() const
{
	return new FPSCounterBehavior;
}
//----------------------------------------------------------------------------//
void FPSCounterBehavior::added()
{
	_fpsCounter.setMaxFramerate(_pOwner->getAttributeAs<int>("maxframerate"));
	_pOwner->addAttribute("fpscounter", new Attribute(&_fpsCounter));
}
//----------------------------------------------------------------------------//
void FPSCounterBehavior::removed()
{
}
//----------------------------------------------------------------------------//
