#include "gamescreenbehavior.h"
//----------------------------------------------------------------------------//
void GameScreenBehavior::activate()
{
	pWorld_->addObject(pWorld_->createObject("Richard"));

	// talk with Jimmy as the game starts
	//pWorld_->broadcast(Message("trigger_condition", std::string("jimmy_talk")));
}
//----------------------------------------------------------------------------//
