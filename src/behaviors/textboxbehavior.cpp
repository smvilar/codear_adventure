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
	// fill with test text
	const char *loremIpsum = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Proin facilisis nulla sed massa sodales iaculis. Etiam et nisi ac massa interdum pulvinar. Aliquam eu urna mauris. Cras sit amet tortor nulla. Praesent eget nisi sit amet erat feugiat congue at et ante. Pellentesque eros justo, dignissim sed egestas et, auctor non nisl. Aliquam erat volutpat. Pellentesque aliquet, leo vel vulputate rhoncus, sapien sem laoreet leo, at egestas augue nisi at velit. Donec sollicitudin, leo id elementum rhoncus, nunc mi consectetur neque, vel placerat nulla diam a massa.";

	GameObject &owner = *pOwner_;

	posX_ = owner["x"];
	posY_ = owner["y"];
	width_ = owner["width"];
	height_ = owner["height"];

	Attribute *fontAttr = owner["font"];
	if (fontAttr)
	{
		std::string fontFilename = fontAttr->get<std::string>();
		ResourceManager &rm = pWorld_->getResourceManager();
		ResourceData res = rm.getResource(fontFilename);
		if (!font_.LoadFromMemory(res.data, res.size))
			std::cerr << "Couldn't load font: " << fontFilename << std::endl;
	}
	else
	{
		font_ = sf::Font::GetDefaultFont();
	}
	text_.SetFont(font_);

	fontSize_ = owner["fontSize"];
	if (fontSize_)
		text_.SetCharacterSize(fontSize_->get<int>());
	else
		text_.SetCharacterSize(12);

	textAttr_ = owner["text"];
	if (textAttr_)
		text_.SetString(textAttr_->get<std::string>());
	else
		text_.SetString(loremIpsum); // fallback to lorem ipsum

	adjustText();
}
//----------------------------------------------------------------------------//
void TextBoxBehavior::update()
{
	text_.SetPosition(posX_->get<int>(), posY_->get<int>());
}
//----------------------------------------------------------------------------//
void TextBoxBehavior::handleMessage(const Message &message)
{
	if (message.equals("update_text"))
	{
		textAttr_ = pOwner_->getAttribute("text");
		if (textAttr_)
		{
			const std::string &text = textAttr_->get<std::string>();
			std::wstring wtext;
			sf::Utf8::ToUtf16(text.begin(), text.end(), std::back_inserter(wtext));
			text_.SetString(wtext);
			adjustText();
		}
	}
}
//----------------------------------------------------------------------------//
void TextBoxBehavior::activate()
{
	pWorld_->getScene().addDrawable(text_, 1);
}
//----------------------------------------------------------------------------//
void TextBoxBehavior::deactivate()
{
	pWorld_->getScene().removeDrawable(text_);
}
//----------------------------------------------------------------------------//
void TextBoxBehavior::adjustText()
{
	// This is a so-called 'cabezeada'

	std::string str = text_.GetString();
	int width = width_->get<int>();

	size_t lastSpace = 0;
	sf::Text t;
	for (size_t i = 0; i < str.size(); ++i)
	{
		std::string substr = str.substr(0, i);
		t.SetString(substr);
		t.SetFont(font_);
		if (fontSize_)
			t.SetCharacterSize(fontSize_->get<int>());
		if (t.GetRect().Width > width)
		{
			// replace the last space found with a new line :)
			str.replace(lastSpace, 1, 1, '\n');
		}
		if (str[i] == ' ')
			lastSpace = i;
	}
	text_.SetString(str);
}
//----------------------------------------------------------------------------//
