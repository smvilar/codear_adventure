#include "core/scene.h"
//----------------------------------------------------------------------------//
#include <SFML/Graphics.hpp>
#include <iostream>
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
	Drawables::iterator it = drawables_.begin();
	for (; it != drawables_.end(); ++it)
	{
		renderTarget.draw(*it->second);
	}
}
//----------------------------------------------------------------------------//
void Scene::addDrawable(sf::Drawable &drawable, s32 layer)
{
	drawables_.insert(std::make_pair(layer, &drawable));
}
//----------------------------------------------------------------------------//
void Scene::removeDrawable(sf::Drawable &drawable)
{
	Drawables::iterator it = drawables_.begin();
	for (; it != drawables_.end(); ++it)
	{
		if (it->second == &drawable)
		{
			drawables_.erase(it);
			return;
		}
	}
}
//----------------------------------------------------------------------------//
void Scene::clearDrawables()
{
	drawables_.clear();
}
//----------------------------------------------------------------------------//
bool Scene::hasDrawable(sf::Drawable &drawable)
{
	Drawables::iterator it = drawables_.begin();
	for (; it != drawables_.end(); ++it)
	{
		if (it->second == &drawable)
			return true;
	}
	return false;
}
//----------------------------------------------------------------------------//
