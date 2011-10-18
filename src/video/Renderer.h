#ifndef HE_RENDERER_H
#define HE_RENDERER_H
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
class Color;
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

	void setClearColor(const Color& color);
	void setTexture(const TexturePtr texture);

	void drawTexture(TexturePtr texture, const Vector2f &pos,
					 const Vector2i &size, f32 angle = 0,
					 const Vector2f &scale = Vector2f(1),
					 const Vector2f &uv1 = Vector2f(0),
					 const Vector2f &uv2 = Vector2f(1));

private:
	DynamicVertexBuffer _dynamicVBO;
};
//----------------------------------------------------------------------------//
} // end namespace he
//----------------------------------------------------------------------------//
#endif // HE_RENDERER_H
