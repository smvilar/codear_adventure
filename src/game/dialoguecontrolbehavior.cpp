#include "dialoguecontrolbehavior.h"
//----------------------------------------------------------------------------//
#include <sstream>
//----------------------------------------------------------------------------//
#include <SFML/Window.hpp>
//----------------------------------------------------------------------------//
#include "gameobject/world.h"
#include "gameobject/message.h"
//----------------------------------------------------------------------------//
void DialogueControlBehavior::activate()
{
	const std::string &filename =
			pOwner_->getAttributeAs<std::string>("dialogueFilename");
	const std::string &text =
			pWorld_->getResourceManager().getTextResource(filename);

	dialogue_.parse(text);

	textAttr_ = pOwner_->getAttribute("text");
	if (!textAttr_)
	{
		textAttr_ = new Attribute(std::string());
		pOwner_->addAttribute("text", textAttr_);
	}
	updateText(dialogue_.getCurrentNode()->getCurrentSpeech());

	displayingAnswers_ = false;
	showingAnswer_ = false;

	mouseUtil_ = pWorld_->getObject("Game")->getAttributeAs<MouseUtil*>("mouse");
}
//----------------------------------------------------------------------------//
void DialogueControlBehavior::update()
{
	if (dialogue_.hasEnded()) return;

	bool textReady = mouseUtil_->justPressed(0) ||
			textClock_.GetElapsedTime() > textTime_;

	if (!showingAnswer_ && textReady)
		nextSpeech();
}
//----------------------------------------------------------------------------//
void DialogueControlBehavior::handleMessage(const Message &message)
{
	if (message.equals("answer_shown"))
	{
		showingAnswer_ = false;
		if (!dialogue_.hasEnded())
			updateText(dialogue_.getCurrentNode()->getCurrentSpeech());
		else
		{
			updateText("");
			pOwner_->removeBehavior(this);
		}
	}
}
//----------------------------------------------------------------------------//
void DialogueControlBehavior::updateText(const std::string &text)
{
	textTime_ = Dialogue::getSpeechTime(text);
	textClock_.Reset();

	textAttr_->setValue(text);
	pOwner_->broadcast(Message("update_text"));
}
//----------------------------------------------------------------------------//
void DialogueControlBehavior::nextSpeech()
{
	if (!dialogue_.getCurrentNode()->hasSpeechEnded())
	{
		dialogue_.getCurrentNode()->nextSpeech();
		updateText(dialogue_.getCurrentNode()->getCurrentSpeech());
	}
	else
	{
		displayAnswers();
	}
}
//----------------------------------------------------------------------------//
void DialogueControlBehavior::displayAnswers()
{
	displayingAnswers_ = true;

	const size_t num = dialogue_.getCurrentNode()->getAnswerQuantity();
	if (num == 1)
	{
		selectAnswer(0);
	}
	else
	{
		std::stringstream answersText;
		for (size_t i = 0; i < num; ++i)
		{
			answersText << (i + 1) << ". ";
			answersText << dialogue_.getCurrentNode()->getAnswer(i);
			answersText << std::endl;
		}
		updateText(answersText.str());
	}
}
//----------------------------------------------------------------------------//
void DialogueControlBehavior::selectAnswer(size_t index)
{
	if (displayingAnswers_ && dialogue_.isValidAnswer(index))
	{
		displayingAnswers_ = false;
		const std::string &answerText = dialogue_.getCurrentNode()->getAnswer(index);
		const std::string &event = dialogue_.selectAnswer(index);

		updateText("");

		if (event != "")
		{
			pWorld_->broadcast(Message("trigger_condition", event));
		}

		showingAnswer_ = true;
		pWorld_->broadcast(Message("show_answer", answerText));
	}
}
//----------------------------------------------------------------------------//
