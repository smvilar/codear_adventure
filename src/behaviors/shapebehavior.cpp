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

	typedef std::vector<Attribute*> AttributeVector;
	const AttributeVector &array = color_->getValue<AttributeVector>();
	sf::Color color(array[0]->getValue<int>(),
					array[1]->getValue<int>(),
					array[2]->getValue<int>(),
					array[3]->getValue<int>());

	sf::FloatRect rect(posX_->getValue<int>(), posY_->getValue<int>(),
					   width_->getValue<int>(), height_->getValue<int>());
	shape_ = sf::Shape::Rectangle(rect, color);
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
