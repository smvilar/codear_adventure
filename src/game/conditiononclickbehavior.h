#ifndef CONDITIONONCLICKBEHAVIOR_H
#define CONDITIONONCLICKBEHAVIOR_H
//----------------------------------------------------------------------------//
#include <hierophantengine.h>
//----------------------------------------------------------------------------//
using namespace he;
//----------------------------------------------------------------------------//
class ConditionOnClickBehavior : public Behavior
{
public:
	Behavior* clone() const { return new ConditionOnClickBehavior; }

	void update();

private:
	void activate();

private:
	MouseUtil *mouseUtil_;
	int posX_, posY_, width_, height_;
	std::string condition_;
};
//----------------------------------------------------------------------------//
#endif // CONDITIONONCLICKBEHAVIOR_H
