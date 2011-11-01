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
	ResourceData res = pWorld_->getResourceManager().getResource(filename);

	soundBuffer_.LoadFromMemory(res.data, res.size);

	sound_.SetBuffer(soundBuffer_);
	if (Attribute* attr = pOwner_->getAttribute("soundLoop"))
		sound_.SetLoop(attr->getValue<bool>());
	if (Attribute* attr = pOwner_->getAttribute("soundAutoPlay"))
		if (attr->getValue<bool>())
			sound_.Play();
}
//----------------------------------------------------------------------------//
void SoundPlayerBehavior::handleMessage(const Message &message)
{
	if (message.equals("sound_play"))
	{
		sound_.Play();
	}
	else if (message.equals("sound_pause"))
	{
		sound_.Pause();
	}
	else if (message.equals("sound_stop"))
	{
		sound_.Stop();
	}
}
//----------------------------------------------------------------------------//
