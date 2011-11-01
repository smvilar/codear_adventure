#include "dialogueactorbehavior.h"
//----------------------------------------------------------------------------//
void DialogueActorBehavior::added()
{
	posX_ = pOwner_->getAttribute("x");
	posY_ = pOwner_->getAttribute("y");
	offsetX_ = pOwner_->getAttribute("dialogueOffsetX");
	offsetY_ = pOwner_->getAttribute("dialogueOffsetY");

	Attribute *fontAttr = pOwner_->getAttribute("font");
	if (fontAttr)
	{
		std::string fontFilename = fontAttr->getValue<std::string>();
		ResourceData res = pWorld_->getResourceManager().getResource(fontFilename);
		if (!font_.LoadFromMemory(res.data, res.size))
			std::cerr << "Couldn't load font: " << fontFilename << std::endl;
	}
	text_.SetFont(font_);

	Attribute *fontSize = pOwner_->getAttribute("fontSize");
	if (fontSize)
		text_.SetCharacterSize(fontSize->getValue<int>());
}
//----------------------------------------------------------------------------//
void DialogueActorBehavior::activate()
{
	pWorld_->getScene().addDrawable(text_);
}
//----------------------------------------------------------------------------//
void DialogueActorBehavior::deactivate()
{
	pWorld_->getScene().removeDrawable(text_);
}
//----------------------------------------------------------------------------//
void DialogueActorBehavior::update()
{
	int x = posX_->getValue<int>() + offsetX_->getValue<int>();
	int y = posY_->getValue<int>() + offsetY_->getValue<int>();
	text_.SetPosition(x, y);

	if (showingAnswer_ && answerClock_.GetElapsedTime() > 1000)
	{
		text_.SetString("");
		pWorld_->broadcast(Message("answer_shown"));
		showingAnswer_ = false;
	}
}
//----------------------------------------------------------------------------//
void DialogueActorBehavior::handleMessage(const Message &message)
{
	if (message.equals("show_answer"))
	{
		std::string text = message.argsAs<std::string>();
		std::wstring wtext;
		sf::Utf8::ToUtf16(text.begin(), text.end(), std::back_inserter(wtext));
		text_.SetString(wtext);
		answerClock_.Reset();
		showingAnswer_ = true;
	}
}
//----------------------------------------------------------------------------//
