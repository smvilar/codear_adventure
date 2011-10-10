#ifndef FORAGERS_SFMLRENDERER_H
#define FORAGERS_SFMLRENDERER_H
//----------------------------------------------------------------------------//
#include "video/RendererImpl.h"
//----------------------------------------------------------------------------//
#include <SFML/Window.hpp>
//----------------------------------------------------------------------------//
namespace foragers
{
//----------------------------------------------------------------------------//
class SFMLRenderer : public RendererImpl
{
public:
	virtual ~SFMLRenderer() {}

	virtual bool init(Window* pWindow);
	virtual void deinit();

	virtual void begin();
	virtual void end();

private:
	sf::Window* _window;
};
//----------------------------------------------------------------------------//
} // end namespace foragers
//----------------------------------------------------------------------------//
#endif // FORAGERS_SFMLRENDERER_H
