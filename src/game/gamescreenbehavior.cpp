#include "gamescreenbehavior.h"
//----------------------------------------------------------------------------//
void GameScreenBehavior::activate()
{
	pWorld_->addObject(pWorld_->createObject("MC"));
}
//----------------------------------------------------------------------------//
