#ifndef FORAGERS_GAME_H
#define FORAGERS_GAME_H
//----------------------------------------------------------------------------//
#include <stack>
//----------------------------------------------------------------------------//
#include "DllExport.h"
#include "core/GameConfig.h"
#include "video/Renderer.h"
#include "resource/ResourceManager.h"
#include "util/FPSCounter.h"
#include "gameobject/gameobject.h"
//----------------------------------------------------------------------------//
namespace sf
{
class Window;
}
//----------------------------------------------------------------------------//
namespace foragers
{
//----------------------------------------------------------------------------//
class Scene;
//----------------------------------------------------------------------------//
// Game it's the main class of the engine. You should create a Game object
// with a custom GameConfig and call run with a custom implementation of a
// Scene to start the program.
// It creates everything needed for the game: a Window, an Input system,
// a Renderer, a ResourceManager, etc.
//----------------------------------------------------------------------------//
class ENGINE_API Game : public GameObject
{
public:
	Game(const char *filename = 0);
	~Game();

/// Run loop
public:
	void run(Scene* pStartingScene = 0);

	bool isRunning() const { return _running; }

private:
	bool _running;

	bool init();
	void deinit();
	void update();
	void render();

/// Scene management
public:
	void setScene(Scene* pNewScene);
	void pushScene(Scene* pNewScene);
	void popScene();

private:
	std::stack<Scene*> _sceneStack;

public:
	// This is the function you should call for quitting the game
	void quit();
	void pause();
	void resume();

/// Renderer
public:
	Renderer& getRenderer() { return _renderer; }
private:
	Renderer _renderer;

/// Resource Manager
public:
	ResourceManager& getResourceManager() { return _resourceManager; }
private:
	ResourceManager _resourceManager;

/// FPS Counter
public:
	const FPSCounter& getFPSCounter() { return _fpsCounter; }
private:
	FPSCounter _fpsCounter;

/// Window implementation
private:
	sf::Window *_window;
};
//----------------------------------------------------------------------------//
} // end namespace foragers
//----------------------------------------------------------------------------//
#endif // FORAGERS_GAME_H
