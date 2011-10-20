#include "behaviors/fpscounterbehavior.h"
//----------------------------------------------------------------------------//
#include "gameobject/gameobject.h"
//----------------------------------------------------------------------------//
using namespace he;
//----------------------------------------------------------------------------//
void FPSCounterBehavior::update()
{
	fpsCounter_.tick();
}
//----------------------------------------------------------------------------//
Behavior* FPSCounterBehavior::clone() const
{
	return new FPSCounterBehavior;
}
//----------------------------------------------------------------------------//
void FPSCounterBehavior::added()
{
	fpsCounter_.setMaxFramerate(pOwner_->getAttributeAs<int>("maxFramerate"));
	pOwner_->addAttribute("fpscounter", new Attribute(&fpsCounter_));
}
//----------------------------------------------------------------------------//
void FPSCounterBehavior::removed()
{
}
//----------------------------------------------------------------------------//
