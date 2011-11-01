#ifndef ACTIONSWITCHTRIGGERBEHAVIOR_H
#define ACTIONSWITCHTRIGGERBEHAVIOR_H
//----------------------------------------------------------------------------//
#include <gameobject/behavior.h>
//----------------------------------------------------------------------------//
using namespace he;
//----------------------------------------------------------------------------//
class ActionSwitchTriggerBehavior : public Behavior
{
public:
	virtual Behavior* clone() const { return new ActionSwitchTriggerBehavior; }

	virtual void handleMessage(const Message &message);
};
//----------------------------------------------------------------------------//
#endif // ACTIONSWITCHTRIGGERBEHAVIOR_H
