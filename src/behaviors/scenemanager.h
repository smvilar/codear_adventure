#ifndef FORAGERS_SCENEMANAGER_H
#define FORAGERS_SCENEMANAGER_H
//----------------------------------------------------------------------------//
#include <stack>
//----------------------------------------------------------------------------//
#include "DllExport.h"
#include "gameobject/gobehavior.h"
//----------------------------------------------------------------------------//
namespace foragers {
//----------------------------------------------------------------------------//
class Scene;
//----------------------------------------------------------------------------//
class ENGINE_API SceneManager : public Behavior
{
public:
	virtual void update();
	virtual void handleMessage(const char *message, void *args);
	virtual Behavior* clone() const;

private:
	void render();

	void changeScene(Scene* pNewScene);
	void pushScene(Scene* pNewScene);
	void popScene();

	std::stack<Scene*> _sceneStack;
};
//----------------------------------------------------------------------------//
} // end namespace foragers
//----------------------------------------------------------------------------//
#endif // FORAGERS_SCENEMANAGER_H
