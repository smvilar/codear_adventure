#include "game/logobehavior.h"
//----------------------------------------------------------------------------//
#include "gameobject/world.h"
#include "gameobject/message.h"
#include "gameobject/gameobject.h"
#include "util/FPSCounter.h"
//----------------------------------------------------------------------------//
using namespace he;
//----------------------------------------------------------------------------//
void LogoBehavior::activate()
{
	fpsCounter_ = pWorld_->getObject("Game")->getAttributeAs<FPSCounter*>("fpsCounter");
	logoTime_ = pOwner_->getAttributeAs<int>("logo_time");
	timer_ = 0;
}
//----------------------------------------------------------------------------//
void LogoBehavior::update()
{
	timer_ += fpsCounter_->getDT();
	if (timer_ > logoTime_)
	{
		Message m("screen_transition", boost::any(std::string("timeout")));
		pWorld_->getObject("Game")->broadcast(m);
	}
}
//----------------------------------------------------------------------------//
