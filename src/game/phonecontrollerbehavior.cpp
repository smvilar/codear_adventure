#include "phonecontrollerbehavior.h"
//----------------------------------------------------------------------------//
#include "dialoguecontrolbehavior.h"
//----------------------------------------------------------------------------//
PhoneControllerBehavior::PhoneControllerBehavior()
: conversationStarted_(false)
{
	conversationStates_["phone"].state = 0;
	conversationStates_["phone"].filenames.push_back("dialogues/phone_dialogue1.json");
	conversationStates_["jimmy"].state = 0;
	conversationStates_["jimmy"].filenames.push_back("dialogues/jimmy_dialogue1.json");
	conversationStates_["jimmy"].filenames.push_back("dialogues/jimmy_dialogue2.json");
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
		const std::string &convId = message.argsAs<std::string>();
		const std::string &filename = conversationStates_[convId].step();

		dialogueFilenameAttr_->setValue(filename);
		// add the DialogueControlBehavior
		pOwner_->addBehavior(new DialogueControlBehavior);
	}
}
//----------------------------------------------------------------------------//
