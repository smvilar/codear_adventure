#ifndef FORAGERS_IINPUTLISTENER_H
#define FORAGERS_IINPUTLISTENER_H
//----------------------------------------------------------------------------//
namespace foragers
{
//----------------------------------------------------------------------------//
class IInputListener
{
public:
	virtual ~IInputListener() {}

	virtual void onKeyDown(u32 keyCode) = 0;
	virtual void onKeyUp(u32 keyCode) = 0;
	virtual void onMouseDown(u32 mouseButton) = 0;
	virtual void onMouseUp(u32 mouseButton) = 0;
	virtual void onMouseMove(u32 x, u32 y) = 0;
};
//----------------------------------------------------------------------------//
} // end namespace foragers
//----------------------------------------------------------------------------//
#endif // FORAGERS_IINPUTLISTENER_H
