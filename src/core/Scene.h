#ifndef FORAGERS_SCENE_H
#define FORAGERS_SCENE_H
//----------------------------------------------------------------------------//
#include <vector>
#include "DllExport.h"
//----------------------------------------------------------------------------//
namespace foragers
{
//----------------------------------------------------------------------------//
class Game;
class Entity;
//----------------------------------------------------------------------------//
class ENGINE_API Scene
{
public:
	Scene();
	virtual ~Scene();

	void added(Game* pGame);
	void removed();

	void update();
	void render();

protected:
	Game* _pGame;

	virtual void onInit() {}
	virtual void onDeinit() {}
	virtual void onUpdate() {}
	virtual void onRender() {}

/// Entity management
public:
	void addEntity(Entity* pEntity);
	void removeEntity(Entity* pEntity);
	void clearEntities();
private: // shouldn't be accessed by children classes
	typedef std::vector<Entity*> EntityVector;
	EntityVector _entities;
};
//----------------------------------------------------------------------------//
} // end namespace foragers
//----------------------------------------------------------------------------//
#endif // FORAGERS_SCENE_H
