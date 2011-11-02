#include "dialogueactorbehavior.h"
//----------------------------------------------------------------------------//
void DialogueActorBehavior::added()
{
	posX_ = pOwner_->getAttribute("x");
	posY_ = pOwner_->getAttribute("y");
	offsetX_ = pOwner_->getAttribute("boxOffsetX");
	offsetY_ = pOwner_->getAttribute("boxOffsetY");
}
//----------------------------------------------------------------------------//
void DialogueActorBehavior::activate()
{
	const std::string &textBoxName =
			pOwner_->getAttributeAs<std::string>("answerBox");
	answerTextBox_ = pWorld_->getObject(textBoxName);
	textBoxColor_ = answerTextBox_->getAttribute("color");
	setText("");
}
//----------------------------------------------------------------------------//
void DialogueActorBehavior::update()
{
	int x = posX_->getValue<int>() + offsetX_->getValue<int>();
	int y = posY_->getValue<int>() + offsetY_->getValue<int>();
	answerTextBox_->getAttribute("x")->setValue(x);
	answerTextBox_->getAttribute("y")->setValue(y);

	const int answerTime = 3000;
	if (showingAnswer_ && answerClock_.GetElapsedTime() > answerTime)
	{
		setText("");
		pWorld_->broadcast(Message("answer_shown"));
		showingAnswer_ = false;
	}
}
//----------------------------------------------------------------------------//
void DialogueActorBehavior::handleMessage(const Message &message)
{
	if (message.equals("show_answer"))
	{
		setText(message.argsAs<std::string>());
		answerClock_.Reset();
		showingAnswer_ = true;
	}
}
//----------------------------------------------------------------------------//
void DialogueActorBehavior::setText(const std::string &text)
{
	answerTextBox_->getAttribute("text")->setValue(text);
	answerTextBox_->broadcast(Message("update_text"));

	typedef std::vector<Attribute*> AttributeVector;
	const AttributeVector &array = textBoxColor_->getValue<AttributeVector>();
	int alpha = (text == "") ? 0 : 64;
	array[3]->setValue(alpha);
}
//----------------------------------------------------------------------------//
