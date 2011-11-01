#include "conditiononclickbehavior.h"
//----------------------------------------------------------------------------//
void ConditionOnClickBehavior::update()
{
	if (mouseUtil_->justPressedBox(0, posX_, posY_, width_, height_))
	{
		pWorld_->broadcast(Message("trigger_condition", condition_));
	}
}
//----------------------------------------------------------------------------//
void ConditionOnClickBehavior::activate()
{
	mouseUtil_ = pWorld_->getObject("Game")->getAttributeAs<MouseUtil*>("mouse");

	posX_ = pOwner_->getAttributeAs<int>("x");
	posY_ = pOwner_->getAttributeAs<int>("y");
	width_ = pOwner_->getAttributeAs<int>("width");
	height_ = pOwner_->getAttributeAs<int>("height");

	condition_ = pOwner_->getAttributeAs<std::string>("condition");
}
//----------------------------------------------------------------------------//
