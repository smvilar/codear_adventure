#include "core/Scene.h"
//----------------------------------------------------------------------------//
#include "core/Entity.h"
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
	for (size_t i=0; i<_entities.size(); ++i)
		_entities[i]->update(dt);
}
//----------------------------------------------------------------------------//
void Scene::render(Renderer &renderer)
{
	// render entities
	for (size_t i=0; i<_entities.size(); ++i)
	{
		_entities[i]->render(renderer);
	}
}
//----------------------------------------------------------------------------//
void Scene::addEntity(View* pEntity)
{
	_entities.push_back(pEntity);
}
//----------------------------------------------------------------------------//
void Scene::removeEntity(View* pEntity)
{
	std::remove(_entities.begin(), _entities.end(), pEntity);
}
//----------------------------------------------------------------------------//
void Scene::clearEntities()
{
	_entities.clear();
}
//----------------------------------------------------------------------------//
