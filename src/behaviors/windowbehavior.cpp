#include "behaviors/windowbehavior.h"
//----------------------------------------------------------------------------//
#include <string>
//----------------------------------------------------------------------------//
#include <SFML/Graphics.hpp>
//----------------------------------------------------------------------------//
#include "core/Types.h"
#include "gameobject/gameobject.h"
//----------------------------------------------------------------------------//
using namespace foragers;
//----------------------------------------------------------------------------//
void WindowBehavior::update()
{
	sf::Event event;
	while (_window->PollEvent(event))
	{
		if (event.Type == sf::Event::Closed)
			_pOwner->getAttribute("alive")->setValue(false);
	}
}
//----------------------------------------------------------------------------//
void WindowBehavior::handleMessage(const char *message, void *args)
{
	if (strcmp(message, "window_active") == 0)
	{
		_window->SetActive();
	}
	else if (strcmp(message, "window_display") == 0)
	{
		_window->Display();
	}
}
//----------------------------------------------------------------------------//
Behavior* WindowBehavior::clone() const
{
	return new WindowBehavior;
}
//----------------------------------------------------------------------------//
void WindowBehavior::added()
{
	using std::string;

	u32 width = _pOwner->getAttributeAs<int>("width");
	u32 height = _pOwner->getAttributeAs<int>("height");
	u32 bpp = _pOwner->getAttributeAs<int>("bpp");
	const string &caption = _pOwner->getAttributeAs<string>("name");

	sf::VideoMode videoMode(width, height, bpp);
	sf::ContextSettings contextSettings; // TODO: specify ogl stuff

	_window = new sf::Window(videoMode, caption,
							 sf::Style::Default, contextSettings);

	_pOwner->addAttribute("window", new Attribute(_window));
}
//----------------------------------------------------------------------------//
void WindowBehavior::activate()
{
}
//----------------------------------------------------------------------------//
