#ifndef FORAGERS_WINDOW_H
#define FORAGERS_WINDOW_H
//----------------------------------------------------------------------------//
#include <string>
#include "DllExport.h"
#include "Types.h"
//----------------------------------------------------------------------------//
namespace foragers
{
//----------------------------------------------------------------------------//
class Game;
class Input;
//----------------------------------------------------------------------------//
class ENGINE_API Window
{
public:
	Window(const char* caption,
		u32 width, u32 height, u32 bpp, bool fullscreen);
	~Window();

	void update(Game* pGame, Input* pInput);

	void setCaption(const char* caption);
	const std::string& getCaption() const;

	u32 getWidth() const;
	u32 getHeight() const;
	u32 getBpp() const;
	bool isFullscreen() const;

private:
	std::string _caption;
	u32 _width;
	u32 _height;
	u32 _bpp;
	bool _fullscreen;
};
//----------------------------------------------------------------------------//
#include "Window.inl"
//----------------------------------------------------------------------------//
} // end namespace foragers
//----------------------------------------------------------------------------//
#endif // FORAGERS_WINDOW_H
