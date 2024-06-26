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
class ResourceManager;
//----------------------------------------------------------------------------//
class ENGINE_API AnimatedSprite
{
public:
	AnimatedSprite() : currentAnimation_(0) {}

	bool parse(const std::string &filename, ResourceManager &resMgr);
	void update(u32 elapsedMs);

	void play(const std::string &animation);

	sf::Sprite& getSprite() { return sprite_; }

private:
	void parseAnimation(const Json::Value &root, u32 framesHoriz, u32 framesVert);

private:
	sf::Sprite sprite_;

	typedef std::map<std::string, SpriteAnimation> Animations;
	Animations animations_;
	SpriteAnimation *currentAnimation_;
};
//----------------------------------------------------------------------------//
} // end namespace he
//----------------------------------------------------------------------------//
#endif // HE_ANIMATEDSPRITE_H
