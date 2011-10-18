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

/// View management
public:
	void addView(View *pView);
	void removeView(View *pView);
	void clearViews();

private:
	typedef std::vector<View*> ViewVector;
	ViewVector _views;
};
//----------------------------------------------------------------------------//
} // end namespace he
//----------------------------------------------------------------------------//
#endif // HE_SCENE_H
