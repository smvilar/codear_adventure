#include "gamescreenbehavior.h"
//----------------------------------------------------------------------------//
void GameScreenBehavior::activate()
{
	std::cout << "hola" << std::endl;
	pWorld_->addObject(pWorld_->createObject("MC"));
}
//----------------------------------------------------------------------------//
