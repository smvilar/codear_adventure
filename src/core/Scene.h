#ifndef FORAGERS_SCENE_H
#define FORAGERS_SCENE_H
//----------------------------------------------------------------------------//
#include <vector>
#include "DllExport.h"
//----------------------------------------------------------------------------//
#include "core/Types.h"
//----------------------------------------------------------------------------//
namespace he {
//----------------------------------------------------------------------------//
class Entity;
class Renderer;
class GameObject;
//----------------------------------------------------------------------------//
class ENGINE_API Scene
{
public:
	void added(GameObject *pGame);
	void removed();

	void update(u32 dt);
	void render(Renderer &renderer);

private:
	GameObject* _pGame;

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
} // end namespace he
//----------------------------------------------------------------------------//
#endif // FORAGERS_SCENE_H
