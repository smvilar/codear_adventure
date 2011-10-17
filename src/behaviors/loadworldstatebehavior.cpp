#include "behaviors/loadworldstatebehavior.h"
//----------------------------------------------------------------------------//
#include "gameobject/world.h"
#include "gameobject/gameobject.h"
//----------------------------------------------------------------------------//
using namespace he;
//----------------------------------------------------------------------------//
void LoadWorldStateBehavior::activate()
{
	using std::string;

	string filename = _pOwner->getAttributeAs<string>("saved_world_state");
	_pWorld->loadState(filename.c_str());
}
//----------------------------------------------------------------------------//
Behavior* LoadWorldStateBehavior::clone() const
{
	return new LoadWorldStateBehavior;
}
//----------------------------------------------------------------------------//
