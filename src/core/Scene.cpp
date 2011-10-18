#include "core/Scene.h"
//----------------------------------------------------------------------------//
#include "core/View.h"
#include "gameobject/gameobject.h"
//----------------------------------------------------------------------------//
using namespace he;
//----------------------------------------------------------------------------//
Scene::~Scene()
{
	clearEntities();
}
//----------------------------------------------------------------------------//
void Scene::update(u32 dt)
{
	// update entities
	for (size_t i=0; i<_views.size(); ++i)
		_views[i]->update(dt);
}
//----------------------------------------------------------------------------//
void Scene::render(Renderer &renderer)
{
	// render entities
	for (size_t i=0; i<_views.size(); ++i)
	{
		_views[i]->render(renderer);
	}
}
//----------------------------------------------------------------------------//
void Scene::addView(View *pView)
{
	_views.push_back(pView);
}
//----------------------------------------------------------------------------//
void Scene::removeView(View *pView)
{
	std::remove(_views.begin(), _views.end(), pView);
}
//----------------------------------------------------------------------------//
void Scene::clearEntities()
{
	_views.clear();
}
//----------------------------------------------------------------------------//
