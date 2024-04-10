#include "behaviors/shapebehavior.h"
//----------------------------------------------------------------------------//
#include "gameobject/gameobject.h"
#include "gameobject/world.h"
//----------------------------------------------------------------------------//
using namespace he;
//----------------------------------------------------------------------------//
void ShapeBehavior::added()
{
	posX_ = pOwner_->getAttribute("x");
	posY_ = pOwner_->getAttribute("y");
	width_ = pOwner_->getAttribute("width");
	height_ = pOwner_->getAttribute("height");
	rotation_ = pOwner_->getAttribute("rotation");
	color_ = pOwner_->getAttribute("color");

	shape_.setSize({ static_cast<float>(width_->get<int>()), static_cast<float>(height_->get<int>()) });
	updateColor();
}
//----------------------------------------------------------------------------//
void ShapeBehavior::update()
{
	shape_.setPosition(posX_->get<int>(), posY_->get<int>());
	updateColor();
}
//----------------------------------------------------------------------------//
void ShapeBehavior::activate()
{
	pWorld_->getScene().addDrawable(shape_, 1);
}
//----------------------------------------------------------------------------//
void ShapeBehavior::deactivate()
{
	pWorld_->getScene().removeDrawable(shape_);
}
//----------------------------------------------------------------------------//
void ShapeBehavior::updateColor()
{
	sf::Color color;
	if (color_)
	{
		typedef std::vector<Attribute*> AttributeVector;
		const AttributeVector &array = color_->get<AttributeVector>();
		color.r = array[0]->get<int>();
		color.g = array[1]->get<int>();
		color.b = array[2]->get<int>();
		color.a = array[3]->get<int>();
	}
	shape_.setFillColor(color);
}
//----------------------------------------------------------------------------//
