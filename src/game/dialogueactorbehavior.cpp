#include "dialogueactorbehavior.h"
//----------------------------------------------------------------------------//
#include "dialogue.h"
//----------------------------------------------------------------------------//
void DialogueActorBehavior::added()
{
	GameObject &owner = *pOwner_;
	posX_ = owner["x"];
	posY_ = owner["y"];
	offsetX_ = owner["boxOffsetX"];
	offsetY_ = owner["boxOffsetY"];
	talkAnim_ = owner["talkAnimation"];
	waitAnim_ = owner["waitAnimation"];
}
//----------------------------------------------------------------------------//
void DialogueActorBehavior::activate()
{
	const std::string &textBoxName =
			pOwner_->getAttributeAs<std::string>("answerBox");
	answerTextBox_ = pWorld_->getObject(textBoxName);
	textBoxColor_ = (*answerTextBox_)["color"];
	setText("");

	mouseUtil_ = pWorld_->getObject("Game")->getAttributeAs<MouseUtil*>("mouse");
}
//----------------------------------------------------------------------------//
void DialogueActorBehavior::update()
{
	int x = posX_->getValue<int>() + offsetX_->getValue<int>();
	int y = posY_->getValue<int>() + offsetY_->getValue<int>();
	(*answerTextBox_)["x"]->setValue(x);
	(*answerTextBox_)["y"]->setValue(y);

	bool ready = mouseUtil_->justPressed(0) ||
			answerClock_.GetElapsedTime() > answerTime_;

	if (showingSpeech_ && ready)
	{
		setText("");
		pWorld_->broadcast(Message("speech_shown"));
		showingSpeech_ = false;

		if (waitAnim_)
		{
			pOwner_->broadcast(Message("play_animation", waitAnim_->getValue<std::string>()));
		}
	}
}
//----------------------------------------------------------------------------//
void DialogueActorBehavior::handleMessage(const Message &message)
{
	if (message.equals("show_speech"))
	{
		setText(message.argsAs<std::string>());
		showingSpeech_ = true;

		if (talkAnim_)
		{
			pOwner_->broadcast(Message("play_animation",
									   talkAnim_->getValue<std::string>()));
		}
	}
}
//----------------------------------------------------------------------------//
void DialogueActorBehavior::setText(const std::string &text)
{
	answerClock_.Reset();
	answerTime_ = Dialogue::getSpeechTime(text);
	(*answerTextBox_)["text"]->setValue(text);
	answerTextBox_->broadcast(Message("update_text"));

	typedef std::vector<Attribute*> AttributeVector;
	const AttributeVector &array = textBoxColor_->getValue<AttributeVector>();
	int alpha = (text == "") ? 0 : 64;
	array[3]->setValue(alpha);
}
//----------------------------------------------------------------------------//
