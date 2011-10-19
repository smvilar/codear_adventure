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
	while (window_->PollEvent(event))
	{
		if (event.Type == sf::Event::Closed)
			pOwner_->getAttribute("alive")->setValue(false);
	}

	// TODO: this should be maybe in another behavior, or gone
	bool isControlPressed = sf::Keyboard::IsKeyPressed(sf::Keyboard::LSystem);
	bool isQPressed = sf::Keyboard::IsKeyPressed(sf::Keyboard::Q);
	if (isControlPressed && isQPressed)
		pOwner_->getAttribute("alive")->setValue(false);

	window_->Clear();
	pWorld_->getScene().render(*window_);
	window_->Display();
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

	u32 width = pOwner_->getAttributeAs<int>("width");
	u32 height = pOwner_->getAttributeAs<int>("height");
	u32 bpp = pOwner_->getAttributeAs<int>("bpp");
	const string &caption = pOwner_->getAttributeAs<string>("name");

	sf::VideoMode videoMode(width, height, bpp);
	sf::ContextSettings contextSettings;

	window_ = new sf::RenderWindow(videoMode, caption,
								   sf::Style::Default, contextSettings);

	pOwner_->addAttribute("window", new Attribute(window_));
}
//----------------------------------------------------------------------------//
