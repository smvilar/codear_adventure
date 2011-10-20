#include "behaviors/textboxbehavior.h"
//----------------------------------------------------------------------------//
#include "gameobject/world.h"
#include "gameobject/gameobject.h"
//----------------------------------------------------------------------------//
using namespace he;
//----------------------------------------------------------------------------//
void TextBoxBehavior::added()
{
	// fill with test text
	const char *testText = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Proin facilisis nulla sed massa sodales iaculis. Etiam et nisi ac massa interdum pulvinar. Aliquam eu urna mauris. Cras sit amet tortor nulla. Praesent eget nisi sit amet erat feugiat congue at et ante. Pellentesque eros justo, dignissim sed egestas et, auctor non nisl. Aliquam erat volutpat. Pellentesque aliquet, leo vel vulputate rhoncus, sapien sem laoreet leo, at egestas augue nisi at velit. Donec sollicitudin, leo id elementum rhoncus, nunc mi consectetur neque, vel placerat nulla diam a massa.";
	text_.SetString(testText);

	posX_ = pOwner_->getAttribute("x");
	posY_ = pOwner_->getAttribute("y");
	width_ = pOwner_->getAttribute("width");
	height_ = pOwner_->getAttribute("height");

	Attribute *fontAttr = pOwner_->getAttribute("font");
	if (fontAttr)
	{
		std::string fontFilename = fontAttr->getValue<std::string>();
		if (!font_.LoadFromFile(fontFilename))
			std::cerr << "Couldn't load font: " << fontFilename << std::endl;
	}
	text_.SetFont(font_);

	fontSize_ = pOwner_->getAttribute("fontSize");
	if (fontSize_)
		text_.SetCharacterSize(fontSize_->getValue<int>());

	textAttr_ = pOwner_->getAttribute("text");
	if (textAttr_)
		text_.SetString(textAttr_->getValue<std::string>());

	adjustText();
}
//----------------------------------------------------------------------------//
void TextBoxBehavior::update()
{
	text_.SetPosition(posX_->getValue<int>(), posY_->getValue<int>());
}
//----------------------------------------------------------------------------//
void TextBoxBehavior::activate()
{
	pWorld_->getScene().addDrawable(&text_);
}
//----------------------------------------------------------------------------//
void TextBoxBehavior::deactivate()
{
	pWorld_->getScene().removeDrawable(&text_);
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
