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
	GameObject& owner = *pOwner_;

	const std::string &filename = owner["dialogueFilename"]->getValue<std::string>();
	const std::string &text =
			pWorld_->getResourceManager().getTextResource(filename);

	dialogue_.parse(text);

	nextSpeech();

	displayingAnswers_ = false;
	showingSpeech_ = false;
}
//----------------------------------------------------------------------------//
void DialogueControlBehavior::handleMessage(const Message &message)
{
	if (message.equals("speech_shown"))
	{
		showingSpeech_ = false;

		if (!dialogue_.hasEnded())
			nextSpeech();
		else
		{
			pOwner_->removeBehavior(this);
		}
	}
}
//----------------------------------------------------------------------------//
void DialogueControlBehavior::nextSpeech()
{
	if (dialogue_.getCurrentNode()->hasSpeechEnded())
	{
		const std::string &event = dialogue_.getCurrentNode()->event;
		if (event != "")
		{
			pWorld_->broadcast(Message("trigger_condition", event));
		}

		dialogue_.next();
	}

	if (!dialogue_.hasEnded())
	{
		const std::string &speech = dialogue_.getCurrentNode()->getCurrentSpeech();
		GameObject* speaker = getSpeaker();
		if (speaker)
		{
			speaker->broadcast(Message("show_speech", speech));
		}
		else
		{
			pOwner_->broadcast(Message("show_speech", speech));
		}
		dialogue_.getCurrentNode()->nextSpeech();
	}
	else // clean all speech boxes
		pWorld_->broadcast(Message("show_speech", std::string("")));
}
//----------------------------------------------------------------------------//
void DialogueControlBehavior::displayAnswers()
{
//	displayingAnswers_ = true;

//	const size_t num = dialogue_.getCurrentNode()->getAnswerQuantity();
//	if (num == 1)
//	{
//		selectAnswer(0);
//	}
//	else
//	{
//		std::stringstream answersText;
//		for (size_t i = 0; i < num; ++i)
//		{
//			answersText << (i + 1) << ". ";
//			answersText << dialogue_.getCurrentNode()->getAnswer(i);
//			answersText << std::endl;
//		}
//		updateText(answersText.str());
//	}
}
//----------------------------------------------------------------------------//
void DialogueControlBehavior::selectAnswer(size_t /*index*/)
{
//	if (displayingAnswers_ && dialogue_.isValidAnswer(index))
//	{
//		displayingAnswers_ = false;
//		const std::string &answerText = dialogue_.getCurrentNode()->getAnswer(index);
//		const std::string &event = dialogue_.selectAnswer(index);

//		updateText("");

//		if (event != "")
//		{
//			pWorld_->broadcast(Message("trigger_condition", event));
//		}

//		showingAnswer_ = true;
//		pWorld_->broadcast(Message("show_answer", answerText));
//	}
}
//----------------------------------------------------------------------------//
GameObject* DialogueControlBehavior::getSpeaker()
{
	GameObject * speaker = pWorld_->getObject(dialogue_.getCurrentNode()->speaker);
	if (speaker && speaker->getAttribute("answerBox"))
		return speaker;
	else
		return 0;
}
//----------------------------------------------------------------------------//
