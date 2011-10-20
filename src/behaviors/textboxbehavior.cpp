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

	sf::FloatRect r = text_.GetRect();
	std::cout << "Rect: (" << r.Left << "," << r.Top << "," << r.Width << "," << r.Height << ")" << std::endl;

	posX_ = pOwner_->getAttribute("pos_x");
	posY_ = pOwner_->getAttribute("pos_y");
	width_ = pOwner_->getAttribute("width");
	height_ = pOwner_->getAttribute("height");

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
	for (size_t i = 0; i < str.size(); ++i)
	{
		if (str[i] == ' ')
			lastSpace = i;
		std::string substr = str.substr(0, i);
		sf::Text t(substr);
		if (t.GetRect().Width > width)
		{
			// replace the last space found with a new line :)
			str.replace(lastSpace, 1, 1, '\n');
		}
	}
	text_.SetString(str);
}
//----------------------------------------------------------------------------//
