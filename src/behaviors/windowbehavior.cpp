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
void WindowBehavior::added()
{
	GameObject &owner = *pOwner_;

	u32 width = owner["width"]->get<int>();
	u32 height = owner["height"]->get<int>();
	u32 bpp = owner["bpp"]->get<int>();
	bool fullscreen = owner["fullscreen"]->get<bool>();
	const std::string &caption = owner["name"]->get<std::string>();

	sf::VideoMode videoMode(width, height, bpp);
	sf::ContextSettings contextSettings;
	u32 style = fullscreen ? sf::Style::Fullscreen : sf::Style::Close;

	window_ = new sf::RenderWindow(videoMode, caption, style, contextSettings);
	window_->SetPosition(0, 0);

	pOwner_->addAttribute("window", new Attribute(window_));
	pOwner_->addAttribute("mouse", new Attribute(&mouseUtil_));
}
//----------------------------------------------------------------------------//
void WindowBehavior::update()
{
	pollEvents();

	const sf::Vector2i &mousePos = sf::Mouse::GetPosition(*window_);
	mouseUtil_.setPosition(mousePos.x, mousePos.y);
	mouseUtil_.setPressed(0, sf::Mouse::IsButtonPressed(sf::Mouse::Left));
	mouseUtil_.setPressed(1, sf::Mouse::IsButtonPressed(sf::Mouse::Right));
	mouseUtil_.setPressed(2, sf::Mouse::IsButtonPressed(sf::Mouse::Middle));

	// TODO: this should be maybe in another behavior, or gone
	bool isControlPressed = sf::Keyboard::IsKeyPressed(sf::Keyboard::LSystem);
	bool isQPressed = sf::Keyboard::IsKeyPressed(sf::Keyboard::Q);
	if (isControlPressed && isQPressed)
		pOwner_->getAttribute("alive")->set(false);

	window_->Clear();
	pWorld_->getScene().render(*window_);
	window_->Display();
}
//----------------------------------------------------------------------------//
void WindowBehavior::pollEvents()
{
	sf::Event event;
	while (window_->PollEvent(event))
	{
		pWorld_->broadcast(Message("window_event", event));
		if (event.Type == sf::Event::Closed)
			pOwner_->getAttribute("alive")->set(false);
	}
}
//----------------------------------------------------------------------------//
