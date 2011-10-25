#include "conditiononclickbehavior.h"
//----------------------------------------------------------------------------//
#include <SFML/Graphics.hpp>
//----------------------------------------------------------------------------//
#include "gameobject/world.h"
#include "gameobject/gameobject.h"
//----------------------------------------------------------------------------//
void ConditionOnClickBehavior::update()
{
	if (sf::Mouse::IsButtonPressed(sf::Mouse::Left))
	{
		const sf::Vector2i &mousePos = sf::Mouse::GetPosition(*window_);
		Recti rect(posX_, posY_, width_, height_);
		if (rect.contains(Vector2i(mousePos.x, mousePos.y)))
		{
			pWorld_->broadcast(Message("trigger_condition", condition_));
		}
	}
}
//----------------------------------------------------------------------------//
void ConditionOnClickBehavior::activate()
{
	window_ = pWorld_->getObject("Game")->getAttributeAs<sf::RenderWindow*>("window");

	posX_ = pOwner_->getAttributeAs<int>("x");
	posY_ = pOwner_->getAttributeAs<int>("y");
	width_ = pOwner_->getAttributeAs<int>("width");
	height_ = pOwner_->getAttributeAs<int>("height");

	condition_ = pOwner_->getAttributeAs<std::string>("condition");
}
//----------------------------------------------------------------------------//
