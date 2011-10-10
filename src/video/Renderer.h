#ifndef FORAGERS_RENDERER_H
#define FORAGERS_RENDERER_H
//----------------------------------------------------------------------------//
#include "DllExport.h"
#include "core/Types.h"
#include "video/DynamicVertexBuffer.h"
#include "video/Texture.h"
//----------------------------------------------------------------------------//
namespace foragers
{
//----------------------------------------------------------------------------//
class Window;
class Texture;
class Color;
class RendererImpl;
//----------------------------------------------------------------------------//
class ENGINE_API Renderer
{
public:
	Renderer();
	~Renderer();

	bool init(Window* pWindow);
	void deinit();

	void begin();
	void end();

	void setClearColor(const Color& color);
	void setTexture(const TexturePtr texture);

	void drawTexture(TexturePtr texture, f32 x, f32 y, u32 w, u32 h, f32 angle, const Vector2f& scale, f32 texX1 = 0.0, f32 texX2 = 1.0, f32 texY1 = 0.0, f32 texY2 = 1.0);

private:
	RendererImpl * const _pImpl;

	DynamicVertexBuffer _dynamicVBO;
};
//----------------------------------------------------------------------------//
} // end namespace foragers
//----------------------------------------------------------------------------//
#endif // FORAGERS_RENDERER_H
