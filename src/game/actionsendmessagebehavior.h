#ifndef ACTIONSENDMESSAGEBEHAVIOR_H
#define ACTIONSENDMESSAGEBEHAVIOR_H
//----------------------------------------------------------------------------//
#include <hierophantengine.h>
//----------------------------------------------------------------------------//
using namespace he;
//----------------------------------------------------------------------------//
class ActionSendMessageBehavior : public Behavior
{
public:
	Behavior* clone() const { return new ActionSendMessageBehavior; }
	void handleMessage(const Message &message);
};
//----------------------------------------------------------------------------//
#endif // ACTIONSENDMESSAGEBEHAVIOR_H
