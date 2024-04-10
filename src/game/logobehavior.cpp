#include "game/logobehavior.h"
//----------------------------------------------------------------------------//
#include "gameobject/world.h"
#include "gameobject/message.h"
#include "gameobject/gameobject.h"
#include "util/fpscounter.h"
//----------------------------------------------------------------------------//
void LogoBehavior::activate()
{
	logoTime_ = pOwner_->getAttributeAs<int>("logo_time");
	clock_.restart();
}
//----------------------------------------------------------------------------//
void LogoBehavior::update()
{
	if (clock_.getElapsedTime().asMilliseconds() > logoTime_)
	{
		clock_.restart();
		pWorld_->broadcast(he::Message("screen_transition",
									   std::string("timeout")));
	}
}
//----------------------------------------------------------------------------//
