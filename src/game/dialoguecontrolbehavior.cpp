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
	const std::string &filename = pOwner_->getAttributeAs<std::string>("dialogueFilename");
	const std::string &text = pWorld_->getResourceManager().getTextResource(filename);
	dialogue_.parse(text);

	textAttr_ = pOwner_->getAttribute("text");
	if (!textAttr_)
	{
		textAttr_ = new Attribute(std::string());
		pOwner_->addAttribute("text", textAttr_);
	}
	updateText(dialogue_.getCurrentNode()->getCurrentSpeech());

	displayingAnswers_ = false;
}
//----------------------------------------------------------------------------//
void DialogueControlBehavior::handleMessage(const Message &message)
{
	if (message.equals("window_event"))
	{
		sf::Event event = *message.argsAs<sf::Event*>();
		if (event.Type == sf::Event::KeyReleased)
		{
			sf::Keyboard::Key keyCode = event.Key.Code;
			if (keyCode == sf::Keyboard::Space)
			{
				nextSpeech();
			}
			else if (keyCode > sf::Keyboard::Num0 &&
					 keyCode < sf::Keyboard::Num5)
			{
				selectAnswer(keyCode - sf::Keyboard::Num1);
			}
		}
	}
	if (message.equals("answer_shown"))
	{
		if (!dialogue_.hasEnded())
			updateText(dialogue_.getCurrentNode()->getCurrentSpeech());
		else
			updateText("");
	}
}
//----------------------------------------------------------------------------//
void DialogueControlBehavior::updateText(const std::string &text)
{
	textAttr_->setValue(text);
	pOwner_->broadcast(Message("update_text"));
}
//----------------------------------------------------------------------------//
void DialogueControlBehavior::displayAnswers()
{
	std::stringstream answersText;
	const size_t num = dialogue_.getCurrentNode()->getAnswerQuantity();
	if (num == 1)
	{
		selectAnswer(0);
	}
	else
	{
		for (size_t i = 0; i < num; ++i)
		{
			answersText << (i + 1) << ". ";
			answersText << dialogue_.getCurrentNode()->getAnswer(i);
			answersText << std::endl;
		}
		updateText(answersText.str());
	}
	displayingAnswers_ = true;
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

		pWorld_->broadcast(Message("show_answer", answerText));
	}
}
//----------------------------------------------------------------------------//
