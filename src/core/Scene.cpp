#include "core/Scene.h"
//----------------------------------------------------------------------------//
#include "core/Entity.h"
#include "gameobject/gameobject.h"
//----------------------------------------------------------------------------//
using namespace he;
//----------------------------------------------------------------------------//
void Scene::added(GameObject *pGame)
{
	_pGame = pGame;
}
//----------------------------------------------------------------------------//
void Scene::removed()
{
	// remove any entity
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
void Scene::addEntity(Entity* pEntity)
{
	_entities.push_back(pEntity);
}
//----------------------------------------------------------------------------//
void Scene::removeEntity(Entity* pEntity)
{
	std::remove(_entities.begin(), _entities.end(), pEntity);
}
//----------------------------------------------------------------------------//
void Scene::clearEntities()
{
	_entities.clear();
}
//----------------------------------------------------------------------------//
