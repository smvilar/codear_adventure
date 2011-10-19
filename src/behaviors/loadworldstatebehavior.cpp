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

	string filename = pOwner_->getAttributeAs<string>("world_filename");
	pWorld_->loadState(filename.c_str());
}
//----------------------------------------------------------------------------//
Behavior* LoadWorldStateBehavior::clone() const
{
	return new LoadWorldStateBehavior;
}
//----------------------------------------------------------------------------//
