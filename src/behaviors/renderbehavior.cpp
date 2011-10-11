#include "behaviors/renderbehavior.h"
//----------------------------------------------------------------------------//
#include "gameobject/world.h"
#include "gameobject/gameobject.h"
//----------------------------------------------------------------------------//
using namespace he;
//----------------------------------------------------------------------------//
void RenderBehavior::update()
{
	_pOwner->broadcast("window_active");

	_renderer.begin();

	_pWorld->getScene().render(_renderer);

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
