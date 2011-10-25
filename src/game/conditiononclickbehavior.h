#ifndef CONDITIONONCLICKBEHAVIOR_H
#define CONDITIONONCLICKBEHAVIOR_H
//----------------------------------------------------------------------------//
#include "hierophantengine.h"
//----------------------------------------------------------------------------//
namespace sf
{
class RenderWindow;
}
//----------------------------------------------------------------------------//
using namespace he;
//----------------------------------------------------------------------------//
class ConditionOnClickBehavior : public Behavior
{
public:
	virtual Behavior* clone() const { return new ConditionOnClickBehavior; }

	virtual void update();

private:
	virtual void activate();

private:
	sf::RenderWindow* window_;
	int posX_, posY_, width_, height_;
	std::string condition_;
};
//----------------------------------------------------------------------------//
#endif // CONDITIONONCLICKBEHAVIOR_H
