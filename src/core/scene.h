#ifndef HE_SCENE_H
#define HE_SCENE_H
//----------------------------------------------------------------------------//
#include <vector>
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
	void addDrawable(sf::Drawable &drawable);
	void removeDrawable(sf::Drawable &drawable);
	void clearDrawables();

private:
	typedef std::vector<sf::Drawable*> ViewVector;
	ViewVector drawables_;
};
//----------------------------------------------------------------------------//
} // end namespace he
//----------------------------------------------------------------------------//
#endif // HE_SCENE_H