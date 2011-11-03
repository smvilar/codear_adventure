#ifndef HE_SPRITEANIMATION_H
#define HE_SPRITEANIMATION_H
//----------------------------------------------------------------------------//
#include "dllexport.h"
#include "core/types.h"
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
					u32 msPerFrame, u32 firstFrame, u32 lastFrame,
					u32 loopCount, u32 loopFromFrame);

	void set(sf::Sprite& sprite, u32 framesHorizontal, u32 framesVertical,
			 u32 msPerFrame, u32 firstFrame, u32 lastFrame,
			 u32 loopCount, u32 loopFromFrame);

	void update(u32 elapsedMs);

	void reset();

private:
	sf::Sprite* sprite_;

	u32 framesHorizontal_;
	u32 framesVertical_;
	u32 msPerFrame_;
	u32 firstFrame_;
	u32 lastFrame_;
	u32 loopCount_;
	u32 loopFromFrame_;

	u32 currentFrame_;
	u32 timer_;
	u32 loopCounter_;

private:
	void updateRect();
};
//----------------------------------------------------------------------------//
} // end namespace he
//----------------------------------------------------------------------------//
#endif // HE_SPRITEANIMATION_H
