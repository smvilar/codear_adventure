#ifndef HE_SOUNDPLAYERBEHAVIOR_H
#define HE_SOUNDPLAYERBEHAVIOR_H
//----------------------------------------------------------------------------//
#include "DllExport.h"
#include "gameobject/behavior.h"
//----------------------------------------------------------------------------//
namespace he {
//----------------------------------------------------------------------------//
class ENGINE_API SoundPlayerBehavior : public Behavior
{
public:
	virtual Behavior* clone() const { return new SoundPlayerBehavior; }

private:
	virtual void activate();


};
//----------------------------------------------------------------------------//
} // end namespace he
//----------------------------------------------------------------------------//
#endif // HE_SOUNDPLAYERBEHAVIOR_H
