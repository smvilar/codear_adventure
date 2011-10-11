#ifndef HE_SPRITE_H
#define HE_SPRITE_H
//----------------------------------------------------------------------------//
#include "DllExport.h"
#include "core/Entity.h"
#include "video/Texture.h"
//----------------------------------------------------------------------------//
namespace he
{
//----------------------------------------------------------------------------//
class Renderer;
class Texture;
//----------------------------------------------------------------------------//
class ENGINE_API Sprite
	: public Entity
{
public:	
	Sprite();
	Sprite(TexturePtr texture, u32 framesHorizontal, u32 framesVertical,
		u32 msPerFrame, u32 firstFrame = 0, u32 lastFrame = 0);

	~Sprite();

	void setTexture(TexturePtr pTexture);
	const TexturePtr getTexture() const;

	virtual void update(u32 elapsedMs);
	virtual void render(Renderer& renderer);

    virtual const Vector2f& getSize() const;

public:
	//void setFramesPerSec(f32 fps);
	//f32 getFramesPerSec() const;

private:
	void textureChanged();

private:
	TexturePtr _pTexture;
	Vector2u _textureSize;

	Vector2f _frameSize;
	u32 _framesHorizontal;
	u32 _framesVertical;
	u32 _currentFrame;
	u32 _firstFrame;
	u32 _lastFrame;
	u32 _frameTimer;
	u32 _msPerFrame;
};
//----------------------------------------------------------------------------//
} // end namespace he
//----------------------------------------------------------------------------//
#endif // HE_SPRITE_H