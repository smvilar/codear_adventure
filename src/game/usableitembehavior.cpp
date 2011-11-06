#include "usableitembehavior.h"
//----------------------------------------------------------------------------//
void UsableItemBehavior::activate()
{
	mouseUtil_ = pWorld_->getObject("Game")->getAttributeAs<MouseUtil*>("mouse");

	posX_ = pOwner_->getAttribute("x");
	posY_ = pOwner_->getAttribute("y");
	width_ = pOwner_->getAttribute("width");
	height_ = pOwner_->getAttribute("height");

	condition_ = pOwner_->getAttribute("condition");
	textToShow_ = pOwner_->getAttribute("overText");

	Attribute *fontAttr = pOwner_->getAttribute("font");
	if (fontAttr)
	{
		std::string fontFilename = fontAttr->get<std::string>();
		ResourceData res = pWorld_->getResourceManager().getResource(fontFilename);
		if (!font_.LoadFromMemory(res.data, res.size))
			std::cerr << "Couldn't load font: " << fontFilename << std::endl;
	}
	text_.SetFont(font_);

	Attribute *fontSize = pOwner_->getAttribute("fontSize");
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
		text_.SetString(textToShow_->get<std::string>());
		text_.SetPosition(mouseUtil_->x, mouseUtil_->y - 30);
		if (!pWorld_->getScene().hasDrawable(text_))
			pWorld_->getScene().addDrawable(text_, 1);

		if (mouseUtil_->justPressed(0))
			pWorld_->broadcast(Message("trigger_condition",
									   condition_->get<std::string>()));
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
