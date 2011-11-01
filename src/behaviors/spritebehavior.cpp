#include "behaviors/spritebehavior.h"
//----------------------------------------------------------------------------//
#include <string>
//----------------------------------------------------------------------------//
#include "gameobject/world.h"
#include "gameobject/gameobject.h"
#include "gameobject/attribute.h"
#include "core/scene.h"
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
	animatedSprite_.parse(pOwner_->getAttributeAs<std::string>("spriteInfo"),
						  pWorld_->getResourceManager().getDefaultResourcePack());

	posX_ = pOwner_->getAttribute("x");
	posY_ = pOwner_->getAttribute("y");
	rotation_ = pOwner_->getAttribute("rotation");
	scale_ = pOwner_->getAttribute("scale");

	sf::Sprite &sprite = animatedSprite_.getSprite();

	if (!pOwner_->getAttribute("width"))
		pOwner_->addAttribute("width", new Attribute(static_cast<int>(sprite.GetSize().x)));
	if (!pOwner_->getAttribute("height"))
		pOwner_->addAttribute("height", new Attribute(static_cast<int>(sprite.GetSize().y)));
}
//----------------------------------------------------------------------------//
void SpriteBehavior::removed()
{
	// clean texture?
}
//----------------------------------------------------------------------------//
void SpriteBehavior::activate()
{
	pWorld_->getScene().addDrawable(animatedSprite_.getSprite());
}
//----------------------------------------------------------------------------//
void SpriteBehavior::deactivate()
{
	pWorld_->getScene().removeDrawable(animatedSprite_.getSprite());
}
//----------------------------------------------------------------------------//
void SpriteBehavior::update()
{
	animatedSprite_.getSprite().SetPosition(posX_->getValue<int>(), posY_->getValue<int>());
	if (scale_)
		animatedSprite_.getSprite().SetScale(scale_->getValue<int>(), scale_->getValue<int>());

	// TODO: unhardcode
	animatedSprite_.update(30);
}
//----------------------------------------------------------------------------//
