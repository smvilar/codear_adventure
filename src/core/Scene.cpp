#include "core/Scene.h"
//----------------------------------------------------------------------------//
#include <SFML/Graphics.hpp>
//----------------------------------------------------------------------------//
#include "video/Renderer.h"
//----------------------------------------------------------------------------//
using namespace he;
//----------------------------------------------------------------------------//
Scene::~Scene()
{
	clearDrawables();
}
//----------------------------------------------------------------------------//
void Scene::render(sf::RenderTarget &renderTarget)
{
	// render views
	for (size_t i=0; i<_drawables.size(); ++i)
		renderTarget.Draw(*_drawables[i]);
}
//----------------------------------------------------------------------------//
void Scene::addDrawable(sf::Drawable *drawable)
{
	_drawables.push_back(drawable);
}
//----------------------------------------------------------------------------//
void Scene::removeDrawable(sf::Drawable *drawable)
{
	std::remove(_drawables.begin(), _drawables.end(), drawable);
}
//----------------------------------------------------------------------------//
void Scene::clearDrawables()
{
	_drawables.clear();
}
//----------------------------------------------------------------------------//
