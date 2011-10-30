#ifndef PHONECONTROLLERBEHAVIOR_H
#define PHONECONTROLLERBEHAVIOR_H
//----------------------------------------------------------------------------//
#include <hierophantengine.h>
//----------------------------------------------------------------------------//
using namespace he;
//----------------------------------------------------------------------------//
class PhoneControllerBehavior : public Behavior
{
public:
	PhoneControllerBehavior();
	virtual Behavior *clone() const { return new PhoneControllerBehavior; }

	virtual void handleMessage(const Message &message);

private:
	virtual void added();

private:
	Attribute *dialogueFilenameAttr_;
	u32 dialogueIndex_;
	bool conversationStarted_;
};
//----------------------------------------------------------------------------//
#endif // PHONECONTROLLERBEHAVIOR_H
