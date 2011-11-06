#include "behaviors/textinputbehavior.h"
//----------------------------------------------------------------------------//
#include <SFML/Window.hpp>
//----------------------------------------------------------------------------//
#include "gameobject/message.h"
#include "gameobject/gameobject.h"
#include "gameobject/attribute.h"
//----------------------------------------------------------------------------//
using namespace he;
//----------------------------------------------------------------------------//
void TextInputBehavior::added()
{
	textAttr_ = pOwner_->getAttribute("text");
}
//----------------------------------------------------------------------------//
void TextInputBehavior::handleMessage(const Message &message)
{
	if (message.equals("window_event"))
	{
		const sf::Event &ev = *message.argsAs<sf::Event*>();
		if (ev.Type == sf::Event::TextEntered)
		{
			sf::String str = ev.Text.Unicode;
			updateText(str.ToAnsiString());
		}
		else if (ev.Type == sf::Event::KeyPressed)
		{
			if (ev.Key.Code == sf::Keyboard::Back)
				backspace();
			if (ev.Key.Code == sf::Keyboard::Return)
				updateText(std::string("\n"));
		}
	}
}
//----------------------------------------------------------------------------//
void TextInputBehavior::updateText(const std::string &str)
{
	if (textAttr_)
	{
		std::string text = textAttr_->get<std::string>();
		text += str;
		textAttr_->set(text);
		pOwner_->broadcast(Message("update_text"));
	}
}
//----------------------------------------------------------------------------//
void TextInputBehavior::backspace()
{
	if (textAttr_)
	{
		std::string text = textAttr_->get<std::string>();
		if (!text.empty())
			text.erase(text.end()-1);
		textAttr_->set(text);
		pOwner_->broadcast(Message("update_text"));
	}
}
//----------------------------------------------------------------------------//
