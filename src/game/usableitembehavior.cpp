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

	overText_ = false;
}
//----------------------------------------------------------------------------//
void UsableItemBehavior::update()
{
	if (mouseUtil_->isInBox(posX_->getValue<int>(),
							posY_->getValue<int>(),
							width_->getValue<int>(),
							height_->getValue<int>()))
	{
		text_.SetString(textToShow_->getValue<std::string>());
		text_.SetPosition(mouseUtil_->x, mouseUtil_->y);
		if (!overText_)
		{
			pWorld_->getScene().addDrawable(text_);
			overText_ = true;
		}

		if (mouseUtil_->justPressed(0))
			pWorld_->broadcast(Message("trigger_condition",
									   condition_->getValue<std::string>()));
	}
	else if (overText_)
	{
		pWorld_->getScene().removeDrawable(text_);
		overText_ = false;
	}
}
//----------------------------------------------------------------------------//
