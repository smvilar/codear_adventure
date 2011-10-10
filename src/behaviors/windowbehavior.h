#ifndef FORAGERS_WINDOWBEHAVIOR_H
#define FORAGERS_WINDOWBEHAVIOR_H
//----------------------------------------------------------------------------//
#include "DllExport.h"
#include "gameobject/gobehavior.h"
//----------------------------------------------------------------------------//
namespace sf
{
class Window;
}
//----------------------------------------------------------------------------//
namespace foragers {
//----------------------------------------------------------------------------//
class ENGINE_API WindowBehavior : public Behavior
{
public:
	virtual void update();
	virtual void handleMessage(const char *message, void *args);
	virtual Behavior* clone() const;

private:
	virtual void added();
	virtual void activate();

private:
	sf::Window *_window;
};
//----------------------------------------------------------------------------//
} // end namespace foragers
//----------------------------------------------------------------------------//
#endif // FORAGERS_WINDOWBEHAVIOR_H
