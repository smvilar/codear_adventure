#include "video/Renderer.h"
//----------------------------------------------------------------------------//
#include <SFML/OpenGL.hpp>
//----------------------------------------------------------------------------//
#include "math/MathUtil.h"
#include "math/Vector2.h"
//----------------------------------------------------------------------------//
using namespace he;
//----------------------------------------------------------------------------//
Renderer::Renderer()
{
}
//----------------------------------------------------------------------------//
Renderer::~Renderer()
{
}
//----------------------------------------------------------------------------//
bool Renderer::init(u32 width, u32 height)
{
	// Init buffers
	_dynamicVBO.init();

	// Set the 2D Projection Matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, width, height, 0, -1, 1);

	// Set alpha blending
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);	
	glEnable(GL_TEXTURE_2D);

	setClearColor(sf::Color::Magenta);

	// init SFML render texture
	_renderTexture.Create(width, height);
	_renderTexture.Clear(sf::Color(0, 0, 0, 0));
	_renderTexture.GetTexture().Bind();
	glGetIntegerv(GL_TEXTURE_BINDING_2D, &_renderTextureID);

	return true;
}
//----------------------------------------------------------------------------//
void Renderer::deinit()
{
	_dynamicVBO.deinit();
}
//----------------------------------------------------------------------------//
void Renderer::begin()
{
	glEnable(GL_CULL_FACE);	
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

}
//----------------------------------------------------------------------------//
void Renderer::end()
{
	_dynamicVBO.render();
}
//----------------------------------------------------------------------------//
void Renderer::setClearColor(const sf::Color& color)
{
	glClearColor(color.r/255.0f, color.g/255.0f, color.b/255.0f, color.a);
}
//----------------------------------------------------------------------------//
void Renderer::setTexture(const TexturePtr texture)
{
	setTexture(texture->getID());
}
//----------------------------------------------------------------------------//
void Renderer::setTexture(s32 textureID)
{
	std::cout << "setting texture " << textureID << std::endl;
	_bindedTextureID = textureID;
}
//----------------------------------------------------------------------------//
void Renderer::drawTexture(TexturePtr texture, const Vector2f &pos,
						   const Vector2i &size, f32 angle,
						   const Vector2f &scale, const Vector2f &uv1,
						   const Vector2f &uv2)
{
	f32 x = pos.x;
	f32 y = pos.y;
	u32 w = size.x;
	u32 h = size.y;

	Vector2f pivot(x + w/2, y + h/2);

	Vector2f a(x, y); 
	Vector2f b(x, y + h); 
	Vector2f c(x + w, y + h); 
	Vector2f d(x + w, y); 

	// Move to (0, 0)
	a -= pivot;
	b -= pivot;
	c -= pivot;
	d -= pivot;

	// Scale
	a.x *= scale.x;	a.y *= scale.y;
	b.x *= scale.x;	b.y *= scale.y;
	c.x *= scale.x;	c.y *= scale.y;
	d.x *= scale.x;	d.y *= scale.y;

	// Rotate
	MathUtil::rotatePoint(a, angle);
	MathUtil::rotatePoint(b, angle);
	MathUtil::rotatePoint(c, angle);
	MathUtil::rotatePoint(d, angle);	

	// Return to original position
	a += pivot;
	b += pivot;
	c += pivot;
	d += pivot;

	_dynamicVBO.setCurrTexture(texture->getID());

	// Add vertexes in CCW otherwise indexing them will fail.
	_dynamicVBO.addVertex(a.x, a.y, uv1.x, uv1.y);
	_dynamicVBO.addVertex(b.x, b.y, uv1.x, uv2.y);
	_dynamicVBO.addVertex(c.x, c.y, uv2.x, uv2.y);
	_dynamicVBO.addVertex(d.x, d.y, uv2.x, uv1.y);
}
//----------------------------------------------------------------------------//
void Renderer::drawRectangle(const Vector2f &pos, const Vector2i &size,
							 const Vector2f &uv1, const Vector2f &uv2)
{
	Vector2f a(pos.x, pos.y);
	Vector2f b(pos.x, pos.y + size.y);
	Vector2f c(pos.x + size.x, pos.y + size.y);
	Vector2f d(pos.x + size.x, pos.y);

	_dynamicVBO.setCurrTexture(_bindedTextureID);

	// Add vertexes in CCW otherwise indexing them will fail.
	_dynamicVBO.addVertex(a.x, a.y, uv1.x, uv1.y);
	_dynamicVBO.addVertex(b.x, b.y, uv1.x, uv2.y);
	_dynamicVBO.addVertex(c.x, c.y, uv2.x, uv2.y);
	_dynamicVBO.addVertex(d.x, d.y, uv2.x, uv1.y);
}
//----------------------------------------------------------------------------//
void Renderer::draw(sf::Drawable &drawable)
{
	_renderTexture.Draw(drawable);
}
//----------------------------------------------------------------------------//
