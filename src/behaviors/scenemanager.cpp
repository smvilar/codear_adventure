#include "behaviors/scenemanager.h"
//----------------------------------------------------------------------------//
#include <string>
//----------------------------------------------------------------------------//
#include "core/Scene.h"
#include "gameobject/gameobject.h"
#include "gameobject/world.h"
#include "gameobject/attribute.h"
#include "video/Renderer.h"
#include "util/FPSCounter.h"
//----------------------------------------------------------------------------//
using namespace he;
//----------------------------------------------------------------------------//
void SceneBehavior::activate()
{
	_pFPSCounter = _pOwner->getAttributeAs<FPSCounter*>("fpscounter");
}
//----------------------------------------------------------------------------//
void SceneBehavior::update()
{
	_pWorld->getScene().update(_pFPSCounter->getDT());
}
//----------------------------------------------------------------------------//
Behavior* SceneBehavior::clone() const
{
	return new SceneBehavior;
}
//----------------------------------------------------------------------------//
