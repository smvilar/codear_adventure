#include "core/Scene.h"
#include "core/Game.h"
#include "core/Entity.h"
#include "util/Profile.h"
//----------------------------------------------------------------------------//
using namespace foragers;
//----------------------------------------------------------------------------//
Scene::Scene()
{
}
//----------------------------------------------------------------------------//
Scene::~Scene()
{
}
//----------------------------------------------------------------------------//
void Scene::added(Game* pGame)
{
	_pGame = pGame;
	onInit();
}
//----------------------------------------------------------------------------//
void Scene::removed()
{
	onDeinit();

	// remove any entity
	clearEntities();
}
//----------------------------------------------------------------------------//
void Scene::update()
{
	onUpdate();

	// update entities
	for (size_t i=0; i<_entities.size(); ++i)
		_entities[i]->update(_pGame->getFPSCounter().getDT());
}
//----------------------------------------------------------------------------//
void Scene::render()
{
	onRender();

	// render entities
	for (size_t i=0; i<_entities.size(); ++i)
	{
		_entities[i]->render(_pGame->getRenderer());
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
