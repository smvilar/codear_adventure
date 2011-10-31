#include "phonecontrollerbehavior.h"
//----------------------------------------------------------------------------//
#include "dialoguecontrolbehavior.h"
//----------------------------------------------------------------------------//
static const char * DIALOGUE_FILENAMES[] = {
	"dialogues/phone_dialogue1.json",
	"dialogues/phone_dialogue2.json"
};
//----------------------------------------------------------------------------//
PhoneControllerBehavior::PhoneControllerBehavior()
: dialogueIndex_(0)
, conversationStarted_(false)
{

}
//----------------------------------------------------------------------------//
void PhoneControllerBehavior::added()
{
	dialogueFilenameAttr_ = pOwner_->getAttribute("dialogueFilename");
	if (!dialogueFilenameAttr_)
	{
		dialogueFilenameAttr_ = new Attribute(std::string());
		pOwner_->addAttribute("dialogueFilename", dialogueFilenameAttr_);
	}
}
//----------------------------------------------------------------------------//
void PhoneControllerBehavior::handleMessage(const Message &message)
{
	if (conversationStarted_) return;

	if (message.equals("start_conversation"))
	{
		// add a dialogue control with some dialogue
		std::string dialogueFilename = DIALOGUE_FILENAMES[dialogueIndex_];
		dialogueFilenameAttr_->setValue(dialogueFilename);

		pOwner_->addBehavior(new DialogueControlBehavior);
	}
}
//----------------------------------------------------------------------------//
