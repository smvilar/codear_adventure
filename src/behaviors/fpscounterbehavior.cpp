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
	_fpsCounter.setMaxFramerate(pOwner_->getAttributeAs<int>("max_framerate"));
	pOwner_->addAttribute("fpscounter", new Attribute(&_fpsCounter));
}
//----------------------------------------------------------------------------//
void FPSCounterBehavior::removed()
{
}
//----------------------------------------------------------------------------//
