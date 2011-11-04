#ifndef OVERTEXTBEHAVIOR_H
#define OVERTEXTBEHAVIOR_H
//----------------------------------------------------------------------------//
#include <hierophantengine.h>
//----------------------------------------------------------------------------//
using namespace he;
//----------------------------------------------------------------------------//
class UsableItemBehavior : public Behavior
{
public:
	Behavior* clone() const { return new UsableItemBehavior; }

	void update();

private:
	void activate();
	void deactivate();

private:
	MouseUtil *mouseUtil_;
	Attribute *posX_, *posY_, *width_, *height_;
	Attribute *condition_;
	Attribute *textToShow_;

	sf::Font font_;
	sf::Text text_;
};
//----------------------------------------------------------------------------//
#endif // OVERTEXTBEHAVIOR_H
