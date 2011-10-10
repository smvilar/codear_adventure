#ifndef FORAGERS_RENDERBEHAVIOR_H
#define FORAGERS_RENDERBEHAVIOR_H
//----------------------------------------------------------------------------//
#include "DllExport.h"
#include "gameobject/gobehavior.h"
#include "video/Renderer.h"
//----------------------------------------------------------------------------//
namespace foragers {
//----------------------------------------------------------------------------//
class ENGINE_API RenderBehavior : public Behavior
{
public:
	virtual void update();
	virtual Behavior* clone() const;

private:
	virtual void added();
	virtual void removed();

private:
	Renderer _renderer;
};
//----------------------------------------------------------------------------//
} // end namespace foragers
//----------------------------------------------------------------------------//
#endif // FORAGERS_RENDERBEHAVIOR_H