#ifndef HE_ADDBEHAVIORBEHAVIOR_H
#define HE_ADDBEHAVIORBEHAVIOR_H
//----------------------------------------------------------------------------//
#include <string>
//----------------------------------------------------------------------------//
#include "hierophantengine.h"
//----------------------------------------------------------------------------//
using namespace he;
//----------------------------------------------------------------------------//
class AddBehaviorBehavior : public Behavior
{
public:
	virtual Behavior* clone() const { return new AddBehaviorBehavior; }

	virtual void handleMessage(const Message &message);

private:
	virtual void added();

private:
	std::string target_;
	std::string behaviorToAdd_;
};
//----------------------------------------------------------------------------//
#endif // HE_ADDBEHAVIORBEHAVIOR_H