#ifndef HE_SCENE_H
#define HE_SCENE_H
//----------------------------------------------------------------------------//
#include <vector>
#include <map>
//----------------------------------------------------------------------------//
#include "dllexport.h"
#include "core/types.h"
//----------------------------------------------------------------------------//
namespace sf
{
class Drawable;
class RenderTarget;
}
//----------------------------------------------------------------------------//
namespace he {
//----------------------------------------------------------------------------//
class ENGINE_API Scene
{
public:
	~Scene();

	void render(sf::RenderTarget &renderTarget);

/// View management
public:
	void addDrawable(sf::Drawable &drawable, s32 layer = 0);
	void removeDrawable(sf::Drawable &drawable);
	void clearDrawables();

	bool hasDrawable(sf::Drawable &drawable);

private:
	typedef std::multimap<s32, sf::Drawable*> Drawables;
	Drawables drawables_;
};
//----------------------------------------------------------------------------//
} // end namespace he
//----------------------------------------------------------------------------//
#endif // HE_SCENE_H
