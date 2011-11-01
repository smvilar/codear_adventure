#ifndef HE_MOUSEUTIL_H
#define HE_MOUSEUTIL_H
//----------------------------------------------------------------------------//
#include "dllexport.h"
#include "core/types.h"
//----------------------------------------------------------------------------//
namespace he {
//----------------------------------------------------------------------------//
class ENGINE_API MouseUtil
{
public:
	s32 x;
	s32 y;

public:
	MouseUtil();

	void setPosition(s32 x, s32 y);
	void setPressed(u32 btnIdx, bool pressed);

	s32 getMovementX() const;
	s32 getMovementY() const;
	bool isPressed(u32 btnIdx) const { return pressed_[btnIdx]; }
	bool justPressed(u32 btnIdx) const;

	bool isInBox(s32 x, s32 y, s32 w, s32 h) const;
	bool justPressedBox(u32 btnIdx, s32 x, s32 y, s32 w, s32 h) const;

private:
	s32 lastX_;
	s32 lastY_;

	bool pressed_[3];
	bool wasPressed_[3];
};
//----------------------------------------------------------------------------//
} // end namespace he
//----------------------------------------------------------------------------//
#endif // HE_MOUSEUTIL_H
