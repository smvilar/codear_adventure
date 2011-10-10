#include "video/Renderer.h"
//----------------------------------------------------------------------------//
// Implementation
#include "SFML/SFMLRenderer.h"
#include <SFML/OpenGL.hpp>
//----------------------------------------------------------------------------//
#include <string>
#include <iostream>
//----------------------------------------------------------------------------//
#include "core/Window.h"
#include "math/MathUtil.h"
#include "math/Vector2.h"
#include "video/Color.h"
//----------------------------------------------------------------------------//
using namespace foragers;
//----------------------------------------------------------------------------//
Renderer::Renderer()
: _pImpl(new SFMLRenderer)
{
}
//----------------------------------------------------------------------------//
Renderer::~Renderer()
{
	delete _pImpl;
}
//----------------------------------------------------------------------------//
bool Renderer::init(Window* pWindow)
{
	using std::string;

	_pImpl->init(pWindow);

	// Init buffers
	_dynamicVBO.init();

	// Set the 2D Projection Matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, pWindow->getWidth(), pWindow->getHeight(), 0, -1, 1);

	// Set alpha blending
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);	
	glEnable(GL_TEXTURE_2D);

	setClearColor(Color::MAGENTA);

	return true;
}
//----------------------------------------------------------------------------//
void Renderer::deinit()
{
	_dynamicVBO.deinit();

	_pImpl->deinit();
}
//----------------------------------------------------------------------------//
void Renderer::begin()
{
	_pImpl->begin();

	glEnable(GL_CULL_FACE);	
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
//----------------------------------------------------------------------------//
void Renderer::end()
{
	_dynamicVBO.render();

	_pImpl->end();
}
//----------------------------------------------------------------------------//
void Renderer::setClearColor(const Color& color)
{
	glClearColor(color.r/255.0f, color.g/255.0f, color.b/255.0f, color.a);
}
//----------------------------------------------------------------------------//
void Renderer::setTexture(const TexturePtr texture)
{
	glBindTexture(GL_TEXTURE_2D, texture->getID());
}
//----------------------------------------------------------------------------//
void Renderer::drawTexture(TexturePtr texture,
	f32 x, f32 y, u32 w, u32 h,
	f32 angle, const Vector2f& scale,
	f32 texX1, f32 texX2, f32 texY1, f32 texY2)
{
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
	_dynamicVBO.addVertex(a.x, a.y, texX1, texY1);
	_dynamicVBO.addVertex(b.x, b.y, texX1, texY2);
	_dynamicVBO.addVertex(c.x, c.y, texX2, texY2);
	_dynamicVBO.addVertex(d.x, d.y, texX2, texY1);	
}
//----------------------------------------------------------------------------//
