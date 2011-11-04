#include "behaviors/textboxbehavior.h"
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

	posX_ = pOwner_->getAttribute("x");
	posY_ = pOwner_->getAttribute("y");
	width_ = pOwner_->getAttribute("width");
	height_ = pOwner_->getAttribute("height");

	Attribute *fontAttr = pOwner_->getAttribute("font");
	if (fontAttr)
	{
		std::string fontFilename = fontAttr->getValue<std::string>();
		ResourceData res = pWorld_->getResourceManager().getResource(fontFilename);
		if (!font_.LoadFromMemory(res.data, res.size))
			std::cerr << "Couldn't load font: " << fontFilename << std::endl;
	}
	text_.SetFont(font_);

	fontSize_ = pOwner_->getAttribute("fontSize");
	if (fontSize_)
		text_.SetCharacterSize(fontSize_->getValue<int>());

	textAttr_ = pOwner_->getAttribute("text");
	if (textAttr_)
		text_.SetString(textAttr_->getValue<std::string>());
	else
		text_.SetString(loremIpsum); // fallback to lorem ipsum

	adjustText();
}
//----------------------------------------------------------------------------//
void TextBoxBehavior::update()
{
	text_.SetPosition(posX_->getValue<int>(), posY_->getValue<int>());
}
//----------------------------------------------------------------------------//
void TextBoxBehavior::handleMessage(const Message &message)
{
	if (message.equals("update_text"))
	{
		textAttr_ = pOwner_->getAttribute("text");
		if (textAttr_)
		{
			const std::string &text = textAttr_->getValue<std::string>();
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
	int width = width_->getValue<int>();

	size_t lastSpace = 0;
	sf::Text t;
	for (size_t i = 0; i < str.size(); ++i)
	{
		std::string substr = str.substr(0, i);
		t.SetString(substr);
		t.SetFont(font_);
		if (fontSize_)
			t.SetCharacterSize(fontSize_->getValue<int>());
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
