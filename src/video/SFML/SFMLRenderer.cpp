#include "SFMLRenderer.h"
//----------------------------------------------------------------------------//
#include <SFML/Graphics.hpp>
//----------------------------------------------------------------------------//
#include "core/Window.h"
//----------------------------------------------------------------------------//
using namespace foragers;
//----------------------------------------------------------------------------//
bool SFMLRenderer::init(Window *pWindow)
{
	sf::VideoMode videoMode(pWindow->getWidth(), pWindow->getHeight(),
							pWindow->getBpp());
	sf::ContextSettings contextSettings; // TODO: specify ogl stuff
	_window = new sf::Window(videoMode, pWindow->getCaption(),
							 sf::Style::Default, contextSettings);

	return true;
}
//----------------------------------------------------------------------------//
void SFMLRenderer::deinit()
{

}
//----------------------------------------------------------------------------//
void SFMLRenderer::begin()
{
	_window->SetActive();
}
//----------------------------------------------------------------------------//
void SFMLRenderer::end()
{
	_window->Display();
}
//----------------------------------------------------------------------------//
