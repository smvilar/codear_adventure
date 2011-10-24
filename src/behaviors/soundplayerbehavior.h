#ifndef HE_SOUNDPLAYERBEHAVIOR_H
#define HE_SOUNDPLAYERBEHAVIOR_H
//----------------------------------------------------------------------------//
#include <SFML/Audio.hpp>
//----------------------------------------------------------------------------//
#include "dllexport.h"
#include "gameobject/behavior.h"
//----------------------------------------------------------------------------//
namespace he {
//----------------------------------------------------------------------------//
class ENGINE_API SoundPlayerBehavior : public Behavior
{
public:
	virtual Behavior* clone() const { return new SoundPlayerBehavior; }
	virtual void handleMessage(const Message &message);

private:
	virtual void activate();

private:
	sf::SoundBuffer soundBuffer_;
	sf::Sound sound_;
};
//----------------------------------------------------------------------------//
} // end namespace he
//----------------------------------------------------------------------------//
#endif // HE_SOUNDPLAYERBEHAVIOR_H
