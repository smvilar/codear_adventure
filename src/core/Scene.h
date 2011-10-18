#ifndef HE_SCENE_H
#define HE_SCENE_H
//----------------------------------------------------------------------------//
#include <vector>
#include "DllExport.h"
//----------------------------------------------------------------------------//
#include "core/Types.h"
//----------------------------------------------------------------------------//
namespace he {
//----------------------------------------------------------------------------//
class View;
class Renderer;
class GameObject;
//----------------------------------------------------------------------------//
class ENGINE_API Scene
{
public:
	~Scene();

	void update(u32 dt);
	void render(Renderer &renderer);

/// Entity management
public:
	void addEntity(View* pEntity);
	void removeEntity(View* pEntity);
	void clearEntities();

private: // shouldn't be accessed by children classes
	typedef std::vector<View*> EntityVector;
	EntityVector _entities;
};
//----------------------------------------------------------------------------//
} // end namespace he
//----------------------------------------------------------------------------//
#endif // HE_SCENE_H
