#include "behaviors/musicplayerbehavior.h"
//----------------------------------------------------------------------------//
#include <iostream>
//----------------------------------------------------------------------------//
#include "gameobject/gameobject.h"
//----------------------------------------------------------------------------//
using namespace he;
//----------------------------------------------------------------------------//
void MusicPlayerBehavior::activate()
{
	music_.OpenFromFile(pOwner_->getAttributeAs<std::string>("musicFilename"));
	if (Attribute* attr = pOwner_->getAttribute("musicLoop"))
		music_.SetLoop(attr->getValue<bool>());
	if (Attribute* attr = pOwner_->getAttribute("musicAutoPlay"))
		if (attr->getValue<bool>())
			music_.Play();
}
//----------------------------------------------------------------------------//
