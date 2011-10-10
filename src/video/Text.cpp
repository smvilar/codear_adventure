#include "video/Text.h"
//----------------------------------------------------------------------------//
#include <sstream>
//----------------------------------------------------------------------------//
#include "resource/ResourceManager.h"
#include "video/Renderer.h"
#include "util/Profile.h"
//----------------------------------------------------------------------------//
using namespace foragers;
//----------------------------------------------------------------------------//
u32 Text::s_textureCount = 0;
//----------------------------------------------------------------------------//
Text::Text()
{
}
//----------------------------------------------------------------------------//
Text::~Text()
{
}
//----------------------------------------------------------------------------//
void Text::load(ResourceManager& resManager, const char* filename)
{
	using std::stringstream;

	_font = resManager.get<Font>(filename);
	
	stringstream ss;
	ss << "Text" << s_textureCount++;
	_texture = resManager.add(ss.str().c_str(), new Texture);
}
//----------------------------------------------------------------------------//
void Text::update(u32 elapsedMs)
{
}
//----------------------------------------------------------------------------//
void Text::render(Renderer& renderer)
{
	renderer.drawTexture(_texture, _position.x, _position.y, 
		_texture->getSize().x, _texture->getSize().y, 0, Vector2f(1, 1));
}
//----------------------------------------------------------------------------//
const Vector2f& Text::getSize() const
{
	return Vector2f::ZERO;
}
//----------------------------------------------------------------------------//
void Text::setText(const char* text, u32 fontSize)
{
	ProfilerBlock p("Text::setText");
	_font->setSize(fontSize);

	const int kWidth = 128;
	const int kHeight = 64;
	u8 buffer[kWidth*kHeight] = {0};
	// create a bitmap with the text
	_font->generateBitmap(text, buffer, kWidth, kHeight);
	// update the texture with the bitmap
	_texture->loadFromMemory(buffer, kWidth, kHeight, 8);
}
//----------------------------------------------------------------------------//
