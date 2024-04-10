#ifndef HE_SHAPEBEHAVIOR_H
#define HE_SHAPEBEHAVIOR_H
//----------------------------------------------------------------------------//
#include <SFML/Graphics.hpp>
//----------------------------------------------------------------------------//
#include "dllexport.h"
#include "gameobject/behavior.h"
//----------------------------------------------------------------------------//
namespace he {
//----------------------------------------------------------------------------//
class Attribute;
//----------------------------------------------------------------------------//
class ENGINE_API ShapeBehavior : public Behavior
{
public:
	virtual Behavior* clone() const { return new ShapeBehavior; }
	virtual void update();

private:
	virtual void added();
	virtual void activate();
	virtual void deactivate();

private:
	sf::RectangleShape shape_;
	Attribute *posX_, *posY_, *width_, *height_;
	Attribute *rotation_, *color_;

private:
	void updateColor();
};
//----------------------------------------------------------------------------//
} // end namespace he
//----------------------------------------------------------------------------//
#endif // HE_SHAPEBEHAVIOR_H
