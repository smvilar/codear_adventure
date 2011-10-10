#include "core/Game.h"
//----------------------------------------------------------------------------//
#include <SFML/Graphics.hpp>
//----------------------------------------------------------------------------//
#include "core/Scene.h"
#include "core/GameConfig.h"
#include "util/Profile.h"
#include "gameobject/objectparser.h"
//----------------------------------------------------------------------------//
using namespace foragers;
//----------------------------------------------------------------------------//
Game::Game(const char *filename)
	: GameObject("Game")
{
	if (filename)
	{
		ObjectParser parser;
		parser.parse(filename, *this);
	}
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
		sf::Event event;
		while (_window->PollEvent(event))
		{
			if (event.Type == sf::Event::Closed)
				quit();
		}

		update();
		render();
		_fpsCounter.tick();
	}
	deinit();
}
//----------------------------------------------------------------------------//
bool Game::init()
{
	using std::string;

	u32 width = getAttributeAs<int>("width");
	u32 height = getAttributeAs<int>("height");
	u32 bpp = getAttributeAs<int>("bpp");
	const string &caption = getAttributeAs<string>("name");

	sf::VideoMode videoMode(width, height, bpp);
	sf::ContextSettings contextSettings; // TODO: specify ogl stuff
	_window = new sf::Window(videoMode, caption,
							 sf::Style::Default, contextSettings);

	return _renderer.init(width, height);
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

	_window->SetActive();
	_renderer.begin();

	// render scene
	if (!_sceneStack.empty())
	{
		_sceneStack.top()->render();
	}

	_renderer.end();
	_window->Display();
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
