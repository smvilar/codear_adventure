#ifndef HE_SCREENDIRECTORBEHAVIOR_H
#define HE_SCREENDIRECTORBEHAVIOR_H
//----------------------------------------------------------------------------//
#include "DllExport.h"
#include "gameobject/behavior.h"
#include "screen/screendirector.h"
//----------------------------------------------------------------------------//
namespace he {
//----------------------------------------------------------------------------//
class ENGINE_API ScreenDirectorBehavior : public Behavior
{
public:
	virtual Behavior* clone() const { return new ScreenDirectorBehavior; }
	virtual void handleMessage(const Message &message);

private:
	virtual void activate();

private:
	ScreenDirector screenDirector_;
	Screen *currentScreen_;
};
//----------------------------------------------------------------------------//
} // end namespace he
//----------------------------------------------------------------------------//
#endif // HE_SCREENDIRECTORBEHAVIOR_H
