#include "behaviors/screendirectorbehavior.h"
//----------------------------------------------------------------------------//
#include <string>
//----------------------------------------------------------------------------//
#include "gameobject/gameobject.h"
#include "gameobject/message.h"
//----------------------------------------------------------------------------//
using namespace he;
//----------------------------------------------------------------------------//
void ScreenDirectorBehavior::activate()
{
	using std::string;

	// Get the screen flow
	string screenFlow = pOwner_->getAttributeAs<string>("screenFlow");
	screenDirector_.parse(screenFlow.c_str());

	// Get the initial screen
	string initialScreen = pOwner_->getAttributeAs<string>("initialScreen");
	screenDirector_.show(initialScreen.c_str(), *pWorld_);
}
//----------------------------------------------------------------------------//
void ScreenDirectorBehavior::handleMessage(const Message &message)
{
	if (message.equals("screen_transition"))
	{
		screenDirector_.transition(message.argsAs<std::string>().c_str(), *pWorld_);
	}
}
//----------------------------------------------------------------------------//
