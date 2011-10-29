#include "game/logobehavior.h"
//----------------------------------------------------------------------------//
#include "gameobject/world.h"
#include "gameobject/message.h"
#include "gameobject/gameobject.h"
#include "util/fpscounter.h"
//----------------------------------------------------------------------------//
void LogoBehavior::activate()
{
	fpsCounter_ = pWorld_->getObject("Game")->getAttributeAs<he::FPSCounter*>("fpsCounter");
	logoTime_ = pOwner_->getAttributeAs<int>("logo_time");
	timer_ = 0;
}
//----------------------------------------------------------------------------//
void LogoBehavior::update()
{
	timer_ += fpsCounter_->getDT();
	if (timer_ > logoTime_)
	{
		pWorld_->broadcast(he::Message("screen_transition",
									   boost::any(std::string("timeout"))));
	}
}
//----------------------------------------------------------------------------//
