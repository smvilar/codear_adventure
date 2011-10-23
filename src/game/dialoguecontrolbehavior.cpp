#include "dialoguecontrolbehavior.h"
//----------------------------------------------------------------------------//
void DialogueControlBehavior::activate()
{
	dialogue_.parse(
		pOwner_->getAttributeAs<std::string>("dialogueFilename").c_str());

	textAttr_ = pOwner_->getAttribute("text");
	if (!textAttr_)
	{
		textAttr_ = new he::Attribute(dialogue_.getCurrentNode()->speech[0]);
		pOwner_->addAttribute("text", textAttr_);
		pOwner_->broadcast(he::Message("update_text"));
	}
}
//----------------------------------------------------------------------------//
void DialogueControlBehavior::update()
{

}
//----------------------------------------------------------------------------//
