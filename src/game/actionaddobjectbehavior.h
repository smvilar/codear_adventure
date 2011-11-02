#ifndef ACTIONADDOBJECTBEHAVIOR_H
#define ACTIONADDOBJECTBEHAVIOR_H
//----------------------------------------------------------------------------//
#include <hierophantengine.h>
//----------------------------------------------------------------------------//
using namespace he;
//----------------------------------------------------------------------------//
class ActionAddObjectBehavior : public Behavior
{
public:
	Behavior* clone() const { return new ActionAddObjectBehavior; }
	void handleMessage(const Message &message);
};
//----------------------------------------------------------------------------//
#endif // ACTIONADDOBJECTBEHAVIOR_H
