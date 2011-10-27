#include "dialoguecontrolbehavior.h"
//----------------------------------------------------------------------------//
#include <sstream>
//----------------------------------------------------------------------------//
#include <SFML/Window.hpp>
//----------------------------------------------------------------------------//
#include "gameobject/message.h"
//----------------------------------------------------------------------------//
void DialogueControlBehavior::activate()
{
	dialogue_.parse(
		pOwner_->getAttributeAs<std::string>("dialogueFilename").c_str());

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
	for (size_t i = 0; i < num; ++i)
	{
		answersText << (i + 1) << ". ";
		answersText << dialogue_.getCurrentNode()->getAnswer(i);
		answersText << std::endl;
	}
	updateText(answersText.str());
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
		dialogue_.selectAnswer(index);
		if (!dialogue_.hasEnded())
			updateText(dialogue_.getCurrentNode()->getCurrentSpeech());
		else
			pOwner_->removeFromWorld();
	}
}
//----------------------------------------------------------------------------//
