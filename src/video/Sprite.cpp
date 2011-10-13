#include "video/Sprite.h"
#include "video/Renderer.h"
//----------------------------------------------------------------------------//
using namespace he;
//----------------------------------------------------------------------------//
Sprite::Sprite()
: _textureSize(0)
, _frameSize(0)
, _framesHorizontal(0)
, _framesVertical(0)
, _currentFrame(0)
, _firstFrame(0)
, _lastFrame(0)
, _frameTimer(0)
, _msPerFrame(0)
{
}
//----------------------------------------------------------------------------//
Sprite::Sprite(TexturePtr texture,
	u32 framesHorizontal, u32 framesVertical, u32 msPerFrame,
	u32 firstFrame, u32 lastFrame)
: _pTexture(texture)
, _framesHorizontal(framesHorizontal)
, _framesVertical(framesVertical)
, _currentFrame(firstFrame)
, _firstFrame(firstFrame)
, _frameTimer(0)
, _msPerFrame(msPerFrame)
{
	if (lastFrame == 0)
		_lastFrame = (_framesHorizontal * _framesVertical) - 1;
	else
		_lastFrame = lastFrame;

	textureChanged();
}
//----------------------------------------------------------------------------//
Sprite::~Sprite()
{
}
//----------------------------------------------------------------------------//
void Sprite::setTexture(TexturePtr pTexture)
{
	_pTexture = pTexture;

	textureChanged();
}
//----------------------------------------------------------------------------//
const TexturePtr Sprite::getTexture() const
{
	return _pTexture;
}
//----------------------------------------------------------------------------//
void Sprite::textureChanged()
{
	if (_pTexture)
	{
		_textureSize = _pTexture->getSize();

		_frameSize.x = (f32)_textureSize.x / _framesHorizontal;
		_frameSize.y = (f32)_textureSize.y / _framesVertical;
	}
	else
	{
		_textureSize = Vector2u::ZERO;
		_frameSize = Vector2f::ZERO;
	}
}
//----------------------------------------------------------------------------//
void Sprite::update(u32 elapsedMs)
{
	_frameTimer += elapsedMs;
	if (_frameTimer >= _msPerFrame)
	{
		++_currentFrame;
		if (_currentFrame > _lastFrame)
			_currentFrame = _firstFrame;
		_frameTimer -= _msPerFrame;
	}
}
//----------------------------------------------------------------------------//
void Sprite::render(Renderer& renderer)
{
	u32 frameX = (_currentFrame % _framesHorizontal) * (u32)_frameSize.x;
	u32 frameY = (_currentFrame / _framesHorizontal) * (u32)_frameSize.y;
	
	f32 frameXBeginf = (f32)frameX / _textureSize.x;
	f32 frameYBeginf = (f32)frameY / _textureSize.y;

	f32 frameXEndf = (f32)(frameX + _frameSize.x) / _textureSize.x;
	f32 frameYEndf = (f32)(frameY + _frameSize.y) / _textureSize.y;

	renderer.drawTexture(_pTexture, getPosition().x, getPosition().y,
		(u32)_frameSize.x, (u32)_frameSize.y, getAngle(), getScale(),
		frameXBeginf, frameXEndf, frameYBeginf, frameYEndf);
}
//----------------------------------------------------------------------------//
const Vector2f& Sprite::getSize() const
{
    return _frameSize;
}
//----------------------------------------------------------------------------//
