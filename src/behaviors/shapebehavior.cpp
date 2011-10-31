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

	sf::Color color;
	if (color_)
	{
		typedef std::vector<Attribute*> AttributeVector;
		const AttributeVector &array = color_->getValue<AttributeVector>();
		color.r = array[0]->getValue<int>();
		color.g = array[1]->getValue<int>();
		color.b = array[2]->getValue<int>();
		color.a = array[3]->getValue<int>();
	}

	sf::FloatRect rect(0, 0, width_->getValue<int>(), height_->getValue<int>());
	shape_ = sf::Shape::Rectangle(rect, color);
}
//----------------------------------------------------------------------------//
void ShapeBehavior::update()
{
	shape_.SetPosition(posX_->getValue<int>(), posY_->getValue<int>());
}
//----------------------------------------------------------------------------//
void ShapeBehavior::activate()
{
	pWorld_->getScene().addDrawable(shape_);
}
//----------------------------------------------------------------------------//
void ShapeBehavior::deactivate()
{
	pWorld_->getScene().removeDrawable(shape_);
}
//----------------------------------------------------------------------------//
