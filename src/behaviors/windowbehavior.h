#ifndef HE_WINDOWBEHAVIOR_H
#define HE_WINDOWBEHAVIOR_H
//----------------------------------------------------------------------------//
#include "DllExport.h"
#include "gameobject/behavior.h"
//----------------------------------------------------------------------------//
namespace sf
{
class Window;
}
//----------------------------------------------------------------------------//
namespace he {
//----------------------------------------------------------------------------//
class ENGINE_API WindowBehavior : public Behavior
{
public:
	virtual void update();
	virtual void handleMessage(const char *message, void *args);
	virtual Behavior* clone() const;

private:
	virtual void added();

private:
	sf::Window *_window;
};
//----------------------------------------------------------------------------//
} // end namespace he
//----------------------------------------------------------------------------//
#endif // HE_WINDOWBEHAVIOR_H
