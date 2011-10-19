#include "video/spriteanimation.h"
//----------------------------------------------------------------------------//
#include <iostream>
//----------------------------------------------------------------------------//
#include <SFML/Graphics.hpp>
//----------------------------------------------------------------------------//
using namespace he;
//----------------------------------------------------------------------------//
SpriteAnimation::SpriteAnimation()
{
	// ...
}
//----------------------------------------------------------------------------//
SpriteAnimation::SpriteAnimation(sf::Sprite &sprite, u32 framesHorizontal,
								 u32 framesVertical, u32 msPerFrame,
								 u32 firstFrame, u32 lastFrame)
: sprite_(&sprite)
, framesHorizontal_(framesHorizontal)
, framesVertical_(framesVertical)
, msPerFrame_(msPerFrame)
, firstFrame_(firstFrame)
, lastFrame_(lastFrame)
{
	// ...
}
//----------------------------------------------------------------------------//
void SpriteAnimation::set(sf::Sprite &sprite, u32 framesHorizontal,
						  u32 framesVertical, u32 msPerFrame,
						  u32 firstFrame, u32 lastFrame)
{
	sprite_ = &sprite;
	framesHorizontal_ = framesHorizontal;
	framesVertical_ = framesVertical;
	msPerFrame_ = msPerFrame;
	firstFrame_ = firstFrame;
	lastFrame_ = lastFrame;

	currentFrame_ = firstFrame_;
	updateRect();
	timer_ = 0;
}
//----------------------------------------------------------------------------//
void SpriteAnimation::update(u32 elapsedMs)
{
	timer_ += elapsedMs;
	if (timer_ > msPerFrame_)
	{
		timer_ -= msPerFrame_;
		u32 maxFrame = lastFrame_
				? lastFrame_
				: (framesHorizontal_ * framesVertical_ - 1);
		currentFrame_++;
		if (currentFrame_ > maxFrame)
			currentFrame_ = firstFrame_;
		updateRect();
	}
}
//----------------------------------------------------------------------------//
void SpriteAnimation::updateRect()
{
	u32 frameWidth = sprite_->GetTexture()->GetWidth() / framesHorizontal_;
	u32 frameHeight = sprite_->GetTexture()->GetHeight() / framesVertical_;

	u32 frameX = (currentFrame_ % framesHorizontal_) * frameWidth;
	u32 frameY = (currentFrame_ / framesHorizontal_) * frameHeight;

	sprite_->SetSubRect(sf::IntRect(frameX, frameY, frameWidth, frameHeight));
}
//----------------------------------------------------------------------------//
