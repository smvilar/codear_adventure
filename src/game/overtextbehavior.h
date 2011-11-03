#ifndef OVERTEXTBEHAVIOR_H
#define OVERTEXTBEHAVIOR_H
//----------------------------------------------------------------------------//
#include <hierophantengine.h>
//----------------------------------------------------------------------------//
using namespace he;
//----------------------------------------------------------------------------//
class OverTextBehavior : public Behavior
{
public:
	Behavior* clone() const { return new OverTextBehavior; }

	void update();

private:
	void activate();

private:
	MouseUtil *mouseUtil_;
	Attribute *posX_, *posY_, *width_, *height_;
	Attribute *textToShow_;

	bool overText_;
	sf::Font font_;
	sf::Text text_;
};
//----------------------------------------------------------------------------//
#endif // OVERTEXTBEHAVIOR_H
