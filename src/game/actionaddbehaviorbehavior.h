#ifndef ACTIONADDBEHAVIORBEHAVIOR_H
#define ACTIONADDBEHAVIORBEHAVIOR_H
//----------------------------------------------------------------------------//
#include <hierophantengine.h>
//----------------------------------------------------------------------------//
using namespace he;
//----------------------------------------------------------------------------//
class ActionAddBehaviorBehavior : public Behavior
{
public:
	Behavior* clone() const { return new ActionAddBehaviorBehavior; }
	void handleMessage(const Message &message);
};
//----------------------------------------------------------------------------//
#endif // ACTIONADDBEHAVIORBEHAVIOR_H
