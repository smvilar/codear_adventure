#ifndef HE_RENDERER_H
#define HE_RENDERER_H
//----------------------------------------------------------------------------//
#include <SFML/Graphics.hpp>
//----------------------------------------------------------------------------//
#include "DllExport.h"
#include "core/Types.h"
#include "video/DynamicVertexBuffer.h"
#include "video/Texture.h"
//----------------------------------------------------------------------------//
namespace he
{
//----------------------------------------------------------------------------//
class Texture;
//----------------------------------------------------------------------------//
class ENGINE_API Renderer
{
public:
	Renderer();
	~Renderer();

	bool init(u32 width, u32 height);
	void deinit();

	void update();

	void begin();
	void end();

	void setClearColor(const sf::Color& color);
	void setTexture(const TexturePtr texture);
	void setTexture(s32 textureID);

	void drawTexture(TexturePtr texture, const Vector2f &pos,
					 const Vector2i &size, f32 angle = 0,
					 const Vector2f &scale = Vector2f(1),
					 const Vector2f &uv1 = Vector2f(0),
					 const Vector2f &uv2 = Vector2f(1));

	void drawRectangle(const Vector2f &pos, const Vector2i &size,
					  const Vector2f &uv1 = Vector2f(0),
					  const Vector2f &uv2 = Vector2f(1));

	void draw(sf::Drawable &drawable);

private:
	DynamicVertexBuffer _dynamicVBO;
	s32 _bindedTextureID;

	sf::RenderTexture _renderTexture;
	s32 _renderTextureID;
};
//----------------------------------------------------------------------------//
} // end namespace he
//----------------------------------------------------------------------------//
#endif // HE_RENDERER_H
