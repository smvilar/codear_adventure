#ifndef HE_TEXTBOXBEHAVIOR_H
#define HE_TEXTBOXBEHAVIOR_H
//----------------------------------------------------------------------------//
#include <SFML/Graphics.hpp>
//----------------------------------------------------------------------------//
#include "DllExport.h"
#include "gameobject/behavior.h"
//----------------------------------------------------------------------------//
namespace he {
//----------------------------------------------------------------------------//
class Attribute;
//----------------------------------------------------------------------------//
class ENGINE_API TextBoxBehavior : public Behavior
{
public:
	virtual Behavior* clone() const { return new TextBoxBehavior; }

private:
	virtual void added();
	virtual void activate();
	virtual void deactivate();

private:
	sf::Text text_;

	Attribute *posX_, *posY_, *width_, *height_;
};
//----------------------------------------------------------------------------//
} // end namespace he
//----------------------------------------------------------------------------//
#endif // HE_TEXTBOXBEHAVIOR_H
