#ifndef HE_SPRITEANIMATION_H
#define HE_SPRITEANIMATION_H
//----------------------------------------------------------------------------//
#include "dllexport.h"
#include "core/Types.h"
//----------------------------------------------------------------------------//
namespace sf
{
class Sprite;
}
//----------------------------------------------------------------------------//
namespace he {
//----------------------------------------------------------------------------//
class ENGINE_API SpriteAnimation
{
public:
	SpriteAnimation();
	SpriteAnimation(sf::Sprite& sprite, u32 framesHorizontal, u32 framesVertical,
					u32 msPerFrame, u32 firstFrame = 0, u32 lastFrame = 0);

	void set(sf::Sprite& sprite, u32 framesHorizontal, u32 framesVertical,
			 u32 msPerFrame, u32 firstFrame = 0, u32 lastFrame = 0);

	void update(u32 elapsedMs);

private:
	sf::Sprite* sprite_;

	u32 framesHorizontal_;
	u32 framesVertical_;
	u32 msPerFrame_;
	u32 firstFrame_;
	u32 lastFrame_;

	u32 currentFrame_;
	u32 timer_;

private:
	void updateRect();
};
//----------------------------------------------------------------------------//
} // end namespace he
//----------------------------------------------------------------------------//
#endif // HE_SPRITEANIMATION_H
