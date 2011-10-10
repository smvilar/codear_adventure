#ifndef FORAGERS_RENDERERIMPL_H
#define FORAGERS_RENDERERIMPL_H
//----------------------------------------------------------------------------//
namespace foragers
{
//----------------------------------------------------------------------------//
class Window;
//----------------------------------------------------------------------------//
class RendererImpl
{
public:
	virtual ~RendererImpl() {}

	virtual bool init(Window* pWindow) = 0;
	virtual void deinit() = 0;
	virtual void begin() = 0;
	virtual void end() = 0;
};
//----------------------------------------------------------------------------//
} // end namespace foragers
//----------------------------------------------------------------------------//
#endif // FORAGERS_RENDERERIMPL_H
