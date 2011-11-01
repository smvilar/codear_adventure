#include "util/mouseutil.h"
//----------------------------------------------------------------------------//
using namespace he;
//----------------------------------------------------------------------------//
MouseUtil::MouseUtil()
: x(0)
, y(0)
, lastX_(0)
, lastY_(0)
{
	pressed_[0] = pressed_[1] = pressed_[2] = false;
	wasPressed_[0] = wasPressed_[1] = wasPressed_[2] = false;
}
//----------------------------------------------------------------------------//
void MouseUtil::setPosition(s32 x, s32 y)
{
	lastX_ = this->x;
	lastY_ = this->y;
	this->x = x;
	this->y = y;
}
//----------------------------------------------------------------------------//
void MouseUtil::setPressed(u32 btnIdx, bool pressed)
{
	wasPressed_[btnIdx] = pressed_[btnIdx];
	pressed_[btnIdx] = pressed;
}
//----------------------------------------------------------------------------//
s32 MouseUtil::getMovementX() const
{
	return x - lastX_;
}
//----------------------------------------------------------------------------//
s32 MouseUtil::getMovementY() const
{
	return y - lastY_;
}
//----------------------------------------------------------------------------//
bool MouseUtil::justPressed(u32 btnIdx) const
{
	return pressed_[btnIdx] && !wasPressed_[btnIdx];
}
//----------------------------------------------------------------------------//
bool MouseUtil::isInBox(s32 x, s32 y, s32 w, s32 h) const
{
	if (this->x < x) return false;
	if (this->x > x + w) return false;
	if (this->y < y) return false;
	if (this->y > y + h) return false;
	return true;
}
//----------------------------------------------------------------------------//
bool MouseUtil::justPressedBox(u32 btnIdx, s32 x, s32 y, s32 w, s32 h) const
{
	return justPressed(btnIdx) && isInBox(x, y, w, h);
}
//----------------------------------------------------------------------------//
