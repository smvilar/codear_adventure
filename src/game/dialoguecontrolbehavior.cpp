#include "dialoguecontrolbehavior.h"
//----------------------------------------------------------------------------//
#include <SFML/Window.hpp>
//----------------------------------------------------------------------------//
void DialogueControlBehavior::activate()
{
	dialogue_.parse(
		pOwner_->getAttributeAs<std::string>("dialogueFilename").c_str());

	textAttr_ = pOwner_->getAttribute("text");
	if (!textAttr_)
	{
		textAttr_ = new he::Attribute(std::string());
		pOwner_->addAttribute("text", textAttr_);
		updateText(dialogue_.getCurrentNode()->getCurrentSpeech());
	}

	displayingAnswers_ = false;
}
//----------------------------------------------------------------------------//
void DialogueControlBehavior::update()
{
	if (sf::Mouse::IsButtonPressed(sf::Mouse::Left))
	{
		std::cout << "clic!" << std::endl;
		if (dialogue_.getCurrentNode()->hasSpeechEnded())
		{
			if (displayingAnswers_)
			{
				displayingAnswers_ = false;
				dialogue_.selectAnswer(0);
			}
			else
			{
				displayingAnswers_ = true;
				displayAnswers();
			}
		}
		else
		{
			dialogue_.getCurrentNode()->nextSpeech();
			updateText(dialogue_.getCurrentNode()->getCurrentSpeech());
		}
	}
}
//----------------------------------------------------------------------------//
void DialogueControlBehavior::updateText(const std::string &text)
{
	textAttr_->setValue(text);
	pOwner_->broadcast(he::Message("update_text"));
}
//----------------------------------------------------------------------------//
void DialogueControlBehavior::displayAnswers()
{
	std::string answersText;
	const size_t num = dialogue_.getCurrentNode()->getAnswerQuantity();
	for (size_t i = 0; i < num; ++i)
	{
		answersText += dialogue_.getCurrentNode()->getAnswer(i);
	}
	updateText(answersText);
}
//----------------------------------------------------------------------------//
