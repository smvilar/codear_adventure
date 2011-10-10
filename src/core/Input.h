#ifndef FORAGERS_INPUT_H
#define FORAGERS_INPUT_H
//----------------------------------------------------------------------------//
#include "DllExport.h"
#include "Types.h"
#include <vector>
//----------------------------------------------------------------------------//
namespace foragers
{
//----------------------------------------------------------------------------//
class IInputListener;
//----------------------------------------------------------------------------//
class ENGINE_API Input
{
public:
	Input();
	~Input();

	void addListener(IInputListener* pListener);
	void removeListener(IInputListener* pListener);

	void keyDown(u32 keyCode);
	void keyUp(u32 keyCode);
	void mouseDown(u32 mouseButton);
	void mouseUp(u32 mouseButton);
	void mouseMove(u32 x, u32 y);

private:
	std::vector<IInputListener*> _listeners;
};
//----------------------------------------------------------------------------//
} // end namespace foragers
//----------------------------------------------------------------------------//
#endif // FORAGERS_INPUT_H
