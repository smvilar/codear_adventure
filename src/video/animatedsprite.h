#ifndef HE_ANIMATEDSPRITE_H
#define HE_ANIMATEDSPRITE_H
//----------------------------------------------------------------------------//
#include <map>
#include <string>
//----------------------------------------------------------------------------//
#include <SFML/Graphics.hpp>
//----------------------------------------------------------------------------//
#include "dllexport.h"
#include "video/spriteanimation.h"
//----------------------------------------------------------------------------//
namespace Json
{
class Value;
}
//----------------------------------------------------------------------------//
namespace he {
//----------------------------------------------------------------------------//
class ENGINE_API AnimatedSprite
{
public:
	bool parse(const std::string &filename);
	void update(u32 elapsedMs);

	void play(const std::string &animation);

	sf::Sprite& getSprite() { return sprite_; }

private:
	void parseAnimation(Json::Value &root, u32 framesHoriz, u32 framesVert);

private:
	sf::Sprite sprite_;
	sf::Texture texture_;

	typedef std::map<std::string, SpriteAnimation> Animations;
	Animations animations_;
	SpriteAnimation *currentAnimation_;
};
//----------------------------------------------------------------------------//
} // end namespace he
//----------------------------------------------------------------------------//
#endif // HE_ANIMATEDSPRITE_H
