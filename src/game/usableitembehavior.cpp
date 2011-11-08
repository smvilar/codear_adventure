#include "usableitembehavior.h"
//----------------------------------------------------------------------------//
#include <iterator>
//----------------------------------------------------------------------------//
void UsableItemBehavior::activate()
{
	mouseUtil_ = pWorld_->getObject("Game")->getAttributeAs<MouseUtil*>("mouse");

	GameObject &owner = *pOwner_;

	posX_ = owner["x"];
	posY_ = owner["y"];
	width_ = owner["width"];
	height_ = owner["height"];

	condition_ = owner["condition"];
	textToShow_ = owner["overText"];

	Attribute *fontAttr = owner["font"];
	if (fontAttr)
	{
		std::string fontFilename = fontAttr->get<std::string>();
		text_.SetFont(pWorld_->getResourceManager().getFont(fontFilename));
	}
	else
		text_.SetFont(sf::Font::GetDefaultFont());

	Attribute *fontSize = owner["fontSize"];
	if (fontSize)
		text_.SetCharacterSize(fontSize->get<int>());
}
//----------------------------------------------------------------------------//
void UsableItemBehavior::update()
{
	if (mouseUtil_->isInBox(posX_->get<int>(),
							posY_->get<int>(),
							width_->get<int>(),
							height_->get<int>()))
	{
		if (textToShow_)
		{
			const std::string &text = textToShow_->get<std::string>();
			std::wstring wtext;
			sf::Utf8::ToUtf16(text.begin(), text.end(), std::back_inserter(wtext));
			text_.SetString(wtext);
			text_.SetPosition(mouseUtil_->x, mouseUtil_->y - 30);
			if (!pWorld_->getScene().hasDrawable(text_))
				pWorld_->getScene().addDrawable(text_, 1);
		}

		if (condition_ && mouseUtil_->justPressed(0))
		{
			pWorld_->broadcast(Message("trigger_condition",
									   condition_->get<std::string>()));
		}
	}
	else if (pWorld_->getScene().hasDrawable(text_))
	{
		pWorld_->getScene().removeDrawable(text_);
	}
}
//----------------------------------------------------------------------------//
void UsableItemBehavior::deactivate()
{
	if (pWorld_->getScene().hasDrawable(text_))
		pWorld_->getScene().removeDrawable(text_);
}
//----------------------------------------------------------------------------//
