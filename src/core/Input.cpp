#include "core/Input.h"
#include "core/IInputListener.h"
//----------------------------------------------------------------------------//
using namespace foragers;
//----------------------------------------------------------------------------//
Input::Input()
{
}
//----------------------------------------------------------------------------//
Input::~Input()
{
}
//----------------------------------------------------------------------------//
void Input::addListener(IInputListener* pListener)
{
	_listeners.push_back(pListener);
}
//----------------------------------------------------------------------------//
void Input::removeListener(IInputListener* pListener)
{
	// TODO: implement!!
}
//----------------------------------------------------------------------------//
void Input::keyDown(u32 keyCode)
{
	size_t listenersSize = _listeners.size();
	for (size_t i=0; i<listenersSize; ++i)
	{
		_listeners[i]->onKeyDown(keyCode);
	}
}
//----------------------------------------------------------------------------//
void Input::keyUp(u32 keyCode)
{
	size_t listenersSize = _listeners.size();
	for (size_t i=0; i<listenersSize; ++i)
	{
		_listeners[i]->onKeyUp(keyCode);
	}
}
//----------------------------------------------------------------------------//
void Input::mouseDown(u32 mouseButton)
{	
	size_t listenersSize = _listeners.size();
	for (size_t i=0; i<listenersSize; ++i)
	{
		_listeners[i]->onMouseDown(mouseButton);
	}
}
//----------------------------------------------------------------------------//
void Input::mouseUp(u32 mouseButton)
{
	size_t listenersSize = _listeners.size();
	for (size_t i=0; i<listenersSize; ++i)
	{
		_listeners[i]->onMouseUp(mouseButton);
	}
}
//----------------------------------------------------------------------------//
void Input::mouseMove(u32 x, u32 y)
{
	size_t listenersSize = _listeners.size();
	for (size_t i=0; i<listenersSize; ++i)
	{
		_listeners[i]->onMouseMove(x, y);
	}
}
//----------------------------------------------------------------------------//
