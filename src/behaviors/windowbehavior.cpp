#include "behaviors/windowbehavior.h"
//----------------------------------------------------------------------------//
#include <string>
//----------------------------------------------------------------------------//
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
//----------------------------------------------------------------------------//
#include "core/Types.h"
#include "gameobject/world.h"
#include "gameobject/gameobject.h"
//----------------------------------------------------------------------------//
using namespace he;
//----------------------------------------------------------------------------//
void WindowBehavior::update()
{
	sf::Event event;
	while (_window->PollEvent(event))
	{
		if (event.Type == sf::Event::Closed)
			_pOwner->getAttribute("alive")->setValue(false);
	}

	// TODO: this should be maybe in another behavior, or gone
	bool isControlPressed = sf::Keyboard::IsKeyPressed(sf::Keyboard::LSystem);
	bool isQPressed = sf::Keyboard::IsKeyPressed(sf::Keyboard::Q);
	if (isControlPressed && isQPressed)
		_pOwner->getAttribute("alive")->setValue(false);

	_window->Clear();
	_pWorld->getScene().render(*_window);
	_window->Display();
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
	sf::ContextSettings contextSettings;

	_window = new sf::RenderWindow(videoMode, caption,
								   sf::Style::Default, contextSettings);

	_pOwner->addAttribute("window", new Attribute(_window));
}
//----------------------------------------------------------------------------//
