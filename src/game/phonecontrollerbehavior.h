#ifndef PHONECONTROLLERBEHAVIOR_H
#define PHONECONTROLLERBEHAVIOR_H
//----------------------------------------------------------------------------//
#include "gameobject/behavior.h"
//----------------------------------------------------------------------------//
using namespace he;
//----------------------------------------------------------------------------//
class PhoneControllerBehavior : public Behavior
{
public:
	virtual Behavior *clone() const { return new PhoneControllerBehavior; }
};
//----------------------------------------------------------------------------//
#endif // PHONECONTROLLERBEHAVIOR_H
