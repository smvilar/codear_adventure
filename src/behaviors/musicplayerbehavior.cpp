#include "behaviors/musicplayerbehavior.h"
//----------------------------------------------------------------------------//
#include "gameobject/gameobject.h"
#include "gameobject/message.h"
#include "gameobject/world.h"
//----------------------------------------------------------------------------//
using namespace he;
//----------------------------------------------------------------------------//
void MusicPlayerBehavior::activate()
{
	std::string filename = pOwner_->getAttributeAs<std::string>("musicFilename");
	ResourceData res = pWorld_->getResourceManager().getResource(filename);

	music_.openFromMemory(res.data, res.size);

	if (Attribute* attr = pOwner_->getAttribute("musicLoop"))
		music_.setLoop(attr->get<bool>());
	if (Attribute* attr = pOwner_->getAttribute("musicAutoPlay"))
		if (attr->get<bool>())
			music_.play();
}
//----------------------------------------------------------------------------//
void MusicPlayerBehavior::handleMessage(const Message &message)
{
	if (message.equals("music_play"))
	{
		music_.play();
	}
	else if (message.equals("music_pause"))
	{
		music_.pause();
	}
	else if (message.equals("music_stop"))
	{
		music_.stop();
	}
}
//----------------------------------------------------------------------------//
