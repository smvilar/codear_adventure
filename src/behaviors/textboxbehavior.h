#ifndef HE_TEXTBOXBEHAVIOR_H
#define HE_TEXTBOXBEHAVIOR_H
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
class ENGINE_API TextBoxBehavior : public Behavior
{
public:
	void update();
	void handleMessage(const Message &message);

	Behavior* clone() const { return new TextBoxBehavior; }

private:
	void added();
	void activate();
	void deactivate();

private:
	sf::Text text_;

	Attribute *posX_, *posY_, *width_, *height_, *fontSize_, *textAttr_;

	void adjustText();
};
//----------------------------------------------------------------------------//
} // end namespace he
//----------------------------------------------------------------------------//
#endif // HE_TEXTBOXBEHAVIOR_H
