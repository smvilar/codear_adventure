#include "behaviors/soundplayerbehavior.h"
//----------------------------------------------------------------------------//
#include "gameobject/gameobject.h"
#include "gameobject/message.h"
#include "gameobject/world.h"
//----------------------------------------------------------------------------//
using namespace he;
//----------------------------------------------------------------------------//
void SoundPlayerBehavior::activate()
{
	std::string filename = pOwner_->getAttributeAs<std::string>("soundFilename");

	sound_.setBuffer(pWorld_->getResourceManager().getSoundBuffer(filename));
	if (Attribute* attr = pOwner_->getAttribute("soundLoop"))
		sound_.setLoop(attr->get<bool>());
	if (Attribute* attr = pOwner_->getAttribute("soundAutoPlay"))
		if (attr->get<bool>())
			sound_.play();
}
//----------------------------------------------------------------------------//
void SoundPlayerBehavior::handleMessage(const Message &message)
{
	if (message.equals("sound_play"))
	{
		sound_.play();
	}
	else if (message.equals("sound_pause"))
	{
		sound_.pause();
	}
	else if (message.equals("sound_stop"))
	{
		sound_.stop();
	}
}
//----------------------------------------------------------------------------//
