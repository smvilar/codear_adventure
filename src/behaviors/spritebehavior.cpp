#include "behaviors/spritebehavior.h"
//----------------------------------------------------------------------------//
#include <string>
//----------------------------------------------------------------------------//
#include "gameobject/world.h"
#include "gameobject/gameobject.h"
#include "gameobject/attribute.h"
#include "gameobject/message.h"
#include "core/scene.h"
//----------------------------------------------------------------------------//
using namespace he;
//----------------------------------------------------------------------------//
void SpriteBehavior::added()
{
	GameObject &owner = *pOwner_;
	posX_ = owner["x"];
	posY_ = owner["y"];
	rotation_ = owner["rotation"];
	scale_ = owner["scale"];
}
//----------------------------------------------------------------------------//
void SpriteBehavior::activate()
{
	Assert((*pOwner_)["spriteInfo"], "Sprite must have the info");

	animatedSprite_.parse(pOwner_->getAttributeAs<std::string>("spriteInfo"),
						 pWorld_->getResourceManager().getDefaultResourcePack());

	sf::Sprite &sprite = animatedSprite_.getSprite();

	if (!(*pOwner_)["width"])
		pOwner_->addAttribute("width", new Attribute(static_cast<int>(sprite.GetSize().x)));
	if (!(*pOwner_)["height"])
		pOwner_->addAttribute("height", new Attribute(static_cast<int>(sprite.GetSize().y)));

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
	animatedSprite_.getSprite().SetPosition(posX_->get<int>(), posY_->get<int>());
	if (rotation_)
		animatedSprite_.getSprite().SetRotation(rotation_->get<int>());
	if (scale_)
		animatedSprite_.getSprite().SetScale(scale_->get<int>(), scale_->get<int>());

	// TODO: unhardcode
	animatedSprite_.update(30);
}
//----------------------------------------------------------------------------//
void SpriteBehavior::handleMessage(const Message &message)
{
	if (message.equals("play_animation"))
	{
		const std::string &name = message.argsAs<std::string>();
		animatedSprite_.play(name);
	}
}
//----------------------------------------------------------------------------//
