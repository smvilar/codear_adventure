#ifndef GAMESCREENBEHAVIOR_H
#define GAMESCREENBEHAVIOR_H
//----------------------------------------------------------------------------//
#include <hierophantengine.h>
//----------------------------------------------------------------------------//
using namespace he;
//----------------------------------------------------------------------------//
class GameScreenBehavior : public Behavior
{
public:
	Behavior* clone() const { return new GameScreenBehavior; }

private:
	void activate();
};
//----------------------------------------------------------------------------//
#endif // GAMESCREENBEHAVIOR_H
