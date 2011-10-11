#ifndef FORAGERS_RENDERER_H
#define FORAGERS_RENDERER_H
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

	void drawTexture(TexturePtr texture, f32 x, f32 y, u32 w, u32 h, f32 angle, const Vector2f& scale, f32 texX1 = 0.0, f32 texX2 = 1.0, f32 texY1 = 0.0, f32 texY2 = 1.0);

private:
	DynamicVertexBuffer _dynamicVBO;
};
//----------------------------------------------------------------------------//
} // end namespace he
//----------------------------------------------------------------------------//
#endif // FORAGERS_RENDERER_H
