#include "behaviors/scenemanager.h"
//----------------------------------------------------------------------------//
#include "core/Scene.h"
#include "core/Game.h"
//----------------------------------------------------------------------------//
using namespace foragers;
//----------------------------------------------------------------------------//
Behavior* SceneManager::clone() const
{
	return new SceneManager;
}
//----------------------------------------------------------------------------//
void SceneManager::update()
{
	// update scene
	if (!_sceneStack.empty())
	{
		_sceneStack.top()->update();
	}
}
//----------------------------------------------------------------------------//
void SceneManager::handleMessage(const char *message, void *args)
{
	if (strcmp(message, "scene_render") == 0)
	{
		render();
	}
}
//----------------------------------------------------------------------------//
void SceneManager::render()
{
	if (!_sceneStack.empty())
	{
		_sceneStack.top()->render();
	}
}
//----------------------------------------------------------------------------//
void SceneManager::changeScene(Scene* newScene)
{
	popScene();
	pushScene(newScene);
}
//----------------------------------------------------------------------------//
void SceneManager::pushScene(Scene* newScene)
{
	newScene->added(static_cast<Game*>(_pOwner));
	_sceneStack.push(newScene);
}
//----------------------------------------------------------------------------//
void SceneManager::popScene()
{
	if (!_sceneStack.empty())
	{
		_sceneStack.top()->removed();
		delete _sceneStack.top();
		_sceneStack.pop();
	}
}
//----------------------------------------------------------------------------//
