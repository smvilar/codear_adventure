#include "core/scene.h"
//----------------------------------------------------------------------------//
#include <SFML/Graphics.hpp>
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
	for (size_t i=0; i<drawables_.size(); ++i)
		renderTarget.Draw(*drawables_[i]);
}
//----------------------------------------------------------------------------//
void Scene::addDrawable(sf::Drawable &drawable)
{
	drawables_.push_back(&drawable);
}
//----------------------------------------------------------------------------//
void Scene::removeDrawable(sf::Drawable &drawable)
{
	drawables_.erase(std::find(drawables_.begin(), drawables_.end(), &drawable));
}
//----------------------------------------------------------------------------//
void Scene::clearDrawables()
{
	drawables_.clear();
}
//----------------------------------------------------------------------------//