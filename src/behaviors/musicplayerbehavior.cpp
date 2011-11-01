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

	music_.OpenFromMemory(res.data, res.size);

	if (Attribute* attr = pOwner_->getAttribute("musicLoop"))
		music_.SetLoop(attr->getValue<bool>());
	if (Attribute* attr = pOwner_->getAttribute("musicAutoPlay"))
		if (attr->getValue<bool>())
			music_.Play();
}
//----------------------------------------------------------------------------//
void MusicPlayerBehavior::handleMessage(const Message &message)
{
	if (message.equals("music_play"))
	{
		music_.Play();
	}
	else if (message.equals("music_pause"))
	{
		music_.Pause();
	}
	else if (message.equals("music_stop"))
	{
		music_.Stop();
	}
}
//----------------------------------------------------------------------------//
