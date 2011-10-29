#include "behaviors/windowbehavior.h"
//----------------------------------------------------------------------------//
#include <string>
//----------------------------------------------------------------------------//
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
//----------------------------------------------------------------------------//
#include "core/types.h"
#include "gameobject/world.h"
#include "gameobject/gameobject.h"
#include "gameobject/message.h"
//----------------------------------------------------------------------------//
using namespace he;
//----------------------------------------------------------------------------//
void WindowBehavior::update()
{
	pollEvents();

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
	bool fullscreen = pOwner_->getAttributeAs<bool>("fullscreen");
	const string &caption = pOwner_->getAttributeAs<string>("name");

	sf::VideoMode videoMode(width, height, bpp);
	sf::ContextSettings contextSettings;
	u32 style = fullscreen ? sf::Style::Fullscreen : sf::Style::Default;

	window_ = new sf::RenderWindow(videoMode, caption, style, contextSettings);

	pOwner_->addAttribute("window", new Attribute(window_));
}
//----------------------------------------------------------------------------//
void WindowBehavior::pollEvents()
{
	sf::Event event;
	while (window_->PollEvent(event))
	{
		pWorld_->broadcast(Message("window_event", &event));
		if (event.Type == sf::Event::Closed)
			pOwner_->getAttribute("alive")->setValue(false);
	}
}
//----------------------------------------------------------------------------//
