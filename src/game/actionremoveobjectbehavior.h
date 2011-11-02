#ifndef ACTIONREMOVEOBJECTBEHAVIOR_H
#define ACTIONREMOVEOBJECTBEHAVIOR_H
//----------------------------------------------------------------------------//
#include <hierophantengine.h>
//----------------------------------------------------------------------------//
using namespace he;
//----------------------------------------------------------------------------//
class ActionRemoveObjectBehavior : public Behavior
{
public:
	Behavior* clone() const { return new ActionRemoveObjectBehavior; }
	void handleMessage(const Message &message);
};
//----------------------------------------------------------------------------//
#endif // ACTIONREMOVEOBJECTBEHAVIOR_H
