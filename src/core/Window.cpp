#include "core/Window.h"
#include "core/Game.h"
#include "core/Input.h"
//----------------------------------------------------------------------------//
using namespace foragers;
//----------------------------------------------------------------------------//
Window::Window(const char* caption,
			   u32 width, u32 height, u32 bpp, bool fullscreen)
: _caption(caption)
, _width(width)
, _height(height)
, _bpp(bpp)
, _fullscreen(fullscreen)
{
}
//----------------------------------------------------------------------------//
Window::~Window()
{
}
//----------------------------------------------------------------------------//
void Window::update(Game* pGame, Input* pInput)
{
#ifdef USE_SDL
	SDL_Event e;
	while (SDL_PollEvent(&e))
	{
		switch (e.type)
		{
		case SDL_QUIT:
			{
				pGame->quit();
			}
		case SDL_ACTIVEEVENT:
			{
				if (e.active.gain)
					pGame->resume();
				else
					pGame->pause();
				/*
				if (e.active.state & SDL_APPACTIVE)
				{
				}
				if (e.active.state & SDL_APPINPUTFOCUS)
				{
				}
				if (e.active.state & SDL_APPMOUSEFOCUS)
				{
				}
				*/
			}
			break;
		case SDL_KEYDOWN:
			{
				pInput->keyDown(e.key.keysym.sym);
			}
			break;
		case SDL_KEYUP:
			{
				pInput->keyUp(e.key.keysym.sym);
			}
			break;
		}
	}
#endif // USE_SDL
}
//----------------------------------------------------------------------------//
void Window::setCaption(const char* caption)
{
	_caption = caption;
#ifdef USE_SDL
	SDL_WM_SetCaption(caption, NULL);
#endif // USE_SDL
}
//----------------------------------------------------------------------------//
