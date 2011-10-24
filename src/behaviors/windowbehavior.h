#ifndef HE_WINDOWBEHAVIOR_H
#define HE_WINDOWBEHAVIOR_H
//----------------------------------------------------------------------------//
#include "dllexport.h"
#include "gameobject/behavior.h"
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
	virtual void update();
	virtual Behavior* clone() const;

private:
	virtual void added();

private:
	sf::RenderWindow *window_;

private:
	void pollEvents();
};
//----------------------------------------------------------------------------//
} // end namespace he
//----------------------------------------------------------------------------//
#endif // HE_WINDOWBEHAVIOR_H
