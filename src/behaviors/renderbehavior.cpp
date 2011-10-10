#include "behaviors/renderbehavior.h"
//----------------------------------------------------------------------------//
#include "gameobject/gameobject.h"
//----------------------------------------------------------------------------//
using namespace foragers;
//----------------------------------------------------------------------------//
void RenderBehavior::update()
{
	_pOwner->broadcast("window_active");

	_renderer.begin();

	_pOwner->broadcast("scene_render", &_renderer);

	_renderer.end();

	_pOwner->broadcast("window_display");
}
//----------------------------------------------------------------------------//
Behavior* RenderBehavior::clone() const
{
	return new RenderBehavior;
}
//----------------------------------------------------------------------------//
void RenderBehavior::added()
{
	u32 width = _pOwner->getAttributeAs<int>("width");
	u32 height = _pOwner->getAttributeAs<int>("height");

	_renderer.init(width, height);

	_pOwner->addAttribute("renderer", new Attribute(&_renderer));
}
//----------------------------------------------------------------------------//
void RenderBehavior::removed()
{
	_renderer.deinit();
	_pOwner->removeAttribute("renderer");
}
//----------------------------------------------------------------------------//
