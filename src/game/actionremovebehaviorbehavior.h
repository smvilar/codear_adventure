#ifndef ACTIONREMOVEBEHAVIORBEHAVIOR_H
#define ACTIONREMOVEBEHAVIORBEHAVIOR_H
//----------------------------------------------------------------------------//
#include <hierophantengine.h>
//----------------------------------------------------------------------------//
using namespace he;
//----------------------------------------------------------------------------//
class ActionRemoveBehaviorBehavior : public Behavior
{
public:
	Behavior* clone() const { return new ActionRemoveBehaviorBehavior; }
	void handleMessage(const Message &message);
};
//----------------------------------------------------------------------------//
#endif // ACTIONREMOVEBEHAVIORBEHAVIOR_H
