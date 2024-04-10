#include "behaviors/textboxbehavior.h"
//----------------------------------------------------------------------------//
#include <iterator>
//----------------------------------------------------------------------------//
#include "gameobject/world.h"
#include "gameobject/gameobject.h"
#include "gameobject/message.h"
//----------------------------------------------------------------------------//
using namespace he;
//----------------------------------------------------------------------------//
void TextBoxBehavior::added()
{
	GameObject &owner = *pOwner_;

	posX_ = owner["x"];
	posY_ = owner["y"];
	width_ = owner["width"];
	height_ = owner["height"];
}
//----------------------------------------------------------------------------//
void TextBoxBehavior::activate()
{
	GameObject &owner = *pOwner_;

	Attribute *fontAttr = owner["font"];
	if (fontAttr)
	{
		std::string fontFilename = fontAttr->get<std::string>();
		text_.setFont(pWorld_->getResourceManager().getFont(fontFilename));
	}

	fontSize_ = owner["fontSize"];
	if (fontSize_)
		text_.setCharacterSize(fontSize_->get<int>());
	else
		text_.setCharacterSize(12);

	updateText();

	// add to gui layer
	pWorld_->getScene().addDrawable(text_, 1);
}
//----------------------------------------------------------------------------//
void TextBoxBehavior::deactivate()
{
	pWorld_->getScene().removeDrawable(text_);
}
//----------------------------------------------------------------------------//
void TextBoxBehavior::update()
{
	text_.setPosition(posX_->get<int>(), posY_->get<int>());
}
//----------------------------------------------------------------------------//
void TextBoxBehavior::handleMessage(const Message &message)
{
	if (message.equals("update_text"))
	{
		updateText();
	}
}
//----------------------------------------------------------------------------//
void TextBoxBehavior::updateText()
{
	textAttr_ = (*pOwner_)["text"];
	if (textAttr_)
	{
		const std::string &text = textAttr_->get<std::string>();
		std::wstring wtext;
		sf::Utf8::toUtf16(text.begin(), text.end(), std::back_inserter(wtext));
		text_.setString(wtext);
		adjustText();
	}
}
//----------------------------------------------------------------------------//
void TextBoxBehavior::adjustText()
{
	// This is a so-called 'cabezeada'

	std::string str = text_.getString();
	int width = width_->get<int>();

	size_t lastSpace = 0;
	sf::Text t;
	for (size_t i = 0; i < str.size(); ++i)
	{
		std::string substr = str.substr(0, i);
		t.setString(substr);
		if (const sf::Font* font = text_.getFont())
			t.setFont(*font);
		if (fontSize_)
			t.setCharacterSize(fontSize_->get<int>());
		if (t.getLocalBounds().width > width)
		{
			// replace the last space found with a new line :)
			str.replace(lastSpace, 1, 1, '\n');
		}
		if (str[i] == ' ')
			lastSpace = i;
	}
	text_.setString(str);
}
//----------------------------------------------------------------------------//
