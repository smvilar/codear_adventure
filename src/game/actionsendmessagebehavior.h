#ifndef ACTIONSENDMESSAGEBEHAVIOR_H
#define ACTIONSENDMESSAGEBEHAVIOR_H
//----------------------------------------------------------------------------//
#include <gameobject/behavior.h>
//----------------------------------------------------------------------------//
using namespace he;
//----------------------------------------------------------------------------//
class ActionSendMessageBehavior : public Behavior
{
public:
	virtual Behavior* clone() const { return new ActionSendMessageBehavior; }

	virtual void handleMessage(const Message &message);
};
//----------------------------------------------------------------------------//
#endif // ACTIONSENDMESSAGEBEHAVIOR_H
