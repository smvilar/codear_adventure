#ifndef HE_WINDOWBEHAVIOR_H
#define HE_WINDOWBEHAVIOR_H
//----------------------------------------------------------------------------//
#include "dllexport.h"
#include "gameobject/behavior.h"
#include "util/mouseutil.h"
//----------------------------------------------------------------------------//
namespace sf
{
class RenderWindow;
}
//----------------------------------------------------------------------------//
namespace he {
//----------------------------------------------------------------------------//
class ENGINE_API WindowBehavior : public Behavior
{
public:
	Behavior* clone() const { return new WindowBehavior; }
	void update();

private:
	void added();

private:
	sf::RenderWindow *window_;
	MouseUtil mouseUtil_;

private:
	void pollEvents();
};
//----------------------------------------------------------------------------//
} // end namespace he
//----------------------------------------------------------------------------//
#endif // HE_WINDOWBEHAVIOR_H
