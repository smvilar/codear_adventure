#include "behaviors/spritebehavior.h"
//----------------------------------------------------------------------------//
#include <string>
//----------------------------------------------------------------------------//
#include "gameobject/world.h"
#include "gameobject/gameobject.h"
#include "gameobject/attribute.h"
#include "core/Scene.h"
//----------------------------------------------------------------------------//
using namespace he;
//----------------------------------------------------------------------------//
Behavior* SpriteBehavior::clone() const
{
	return new SpriteBehavior;
}
//----------------------------------------------------------------------------//
void SpriteBehavior::added()
{
	using std::string;

	const string &filename = pOwner_->getAttributeAs<string>("spriteFilename");

	int framesHorizontal = 1, framesVertical = 1;
	int msPerFrame = 0, firstFrame = 0,	 lastFrame = 0, loopFromFrame = 0;

	readAnimAttr("framesHorizontal", framesHorizontal);
	readAnimAttr("framesVertical", framesVertical);
	readAnimAttr("msPerFrame", msPerFrame);
	readAnimAttr("firstFrame", firstFrame);
	readAnimAttr("lastFrame", lastFrame);
	readAnimAttr("loopFromFrame", loopFromFrame);

	if (!texture_.LoadFromFile(filename))
		std::cerr << "Error loading sprite: " << filename << std::endl;
	sprite_.SetTexture(texture_);

	spriteAnimation_.set(sprite_, framesHorizontal, framesVertical,
						 msPerFrame, firstFrame, lastFrame, loopFromFrame);

	posX_ = pOwner_->getAttribute("x");
	posY_ = pOwner_->getAttribute("y");
	rotation_ = pOwner_->getAttribute("rotation");
	scale_ = pOwner_->getAttribute("scale");

	if (!pOwner_->getAttribute("width"))
		pOwner_->addAttribute("width", new Attribute(static_cast<int>(sprite_.GetSize().x)));
	if (!pOwner_->getAttribute("height"))
		pOwner_->addAttribute("height", new Attribute(static_cast<int>(sprite_.GetSize().y)));
}
//----------------------------------------------------------------------------//
void SpriteBehavior::removed()
{
	// clean texture?
}
//----------------------------------------------------------------------------//
void SpriteBehavior::activate()
{
	pWorld_->getScene().addDrawable(&sprite_);
}
//----------------------------------------------------------------------------//
void SpriteBehavior::deactivate()
{
	pWorld_->getScene().removeDrawable(&sprite_);
}
//----------------------------------------------------------------------------//
void SpriteBehavior::update()
{
	sprite_.SetPosition(posX_->getValue<int>(), posY_->getValue<int>());
	if (scale_)
		sprite_.SetScale(scale_->getValue<int>(), scale_->getValue<int>());

	// TODO: unhardcode
	spriteAnimation_.update(30);
}
//----------------------------------------------------------------------------//
void SpriteBehavior::readAnimAttr(const char *attrName, int &animAttr)
{
	Attribute* attr = pOwner_->getAttribute(attrName);
	if (attr) animAttr = attr->getValue<int>();
}
//----------------------------------------------------------------------------//
