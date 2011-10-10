#include "core/Game.h"
#include "core/Scene.h"
#include "core/GameConfig.h"
#include "util/Profile.h"
//----------------------------------------------------------------------------//
using namespace foragers;
//----------------------------------------------------------------------------//
Game::Game(GameConfig& gameConfig)
: _running(false)
, _window(gameConfig.name.c_str(),
		  gameConfig.screenWidth, gameConfig.screenHeight,
		  gameConfig.screenBpp, gameConfig.fullscreen)
, _fpsCounter(gameConfig.maxFramerate)
{
	// ...
}
//----------------------------------------------------------------------------//
Game::~Game()
{
	// ...
}
//----------------------------------------------------------------------------//
void Game::run(Scene* pStartingScene)
{
	_running = init();

	if (pStartingScene)
	{
		pushScene(pStartingScene);
	}

	while (_running)
	{
		update();
		render();
		_fpsCounter.tick();
	}
	deinit();
}
//----------------------------------------------------------------------------//
bool Game::init()
{
	bool success = _renderer.init(&_window);

	return success;
}
//----------------------------------------------------------------------------//
void Game::deinit()
{
	popScene();

	_renderer.deinit();

	Profiler::clearAll();
}
//----------------------------------------------------------------------------//
void Game::update()
{
	ProfilerBlock p("Game::update");

	// update window and input events
	_window.update(this, &_input);

	// update scene
	if (!_sceneStack.empty())
	{
		_sceneStack.top()->update();
	}
}
//----------------------------------------------------------------------------//
void Game::render()
{
	ProfilerBlock p("Game::render");

	_renderer.begin();

	// render scene
	if (!_sceneStack.empty())
	{
		_sceneStack.top()->render();
	}

	_renderer.end();
}
//----------------------------------------------------------------------------//
void Game::setScene(Scene* newScene)
{
	popScene();
	pushScene(newScene);
}
//----------------------------------------------------------------------------//
void Game::pushScene(Scene* newScene)
{
	newScene->added(this);
	_sceneStack.push(newScene);
}
//----------------------------------------------------------------------------//
void Game::popScene()
{
	if (!_sceneStack.empty())
	{
		_sceneStack.top()->removed();
		delete _sceneStack.top();
		_sceneStack.pop();
	}
}
//----------------------------------------------------------------------------//
void Game::quit()
{
	_running = false;
}
//----------------------------------------------------------------------------//
void Game::pause()
{
}
//----------------------------------------------------------------------------//
void Game::resume()
{
}
//----------------------------------------------------------------------------//
