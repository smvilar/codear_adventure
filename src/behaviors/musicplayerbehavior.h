#ifndef HE_MUSICPLAYERBEHAVIOR_H
#define HE_MUSICPLAYERBEHAVIOR_H
//----------------------------------------------------------------------------//
#include <SFML/Audio.hpp>
//----------------------------------------------------------------------------//
#include "DllExport.h"
#include "gameobject/behavior.h"
//----------------------------------------------------------------------------//
namespace he {
//----------------------------------------------------------------------------//
class ENGINE_API MusicPlayerBehavior : public Behavior
{
public:
	virtual Behavior* clone() const { return new MusicPlayerBehavior; }

private:
	virtual void activate();

private:
	sf::Music music_;
};
//----------------------------------------------------------------------------//
} // end namespace he
//----------------------------------------------------------------------------//
#endif // HE_MUSICPLAYERBEHAVIOR_H
