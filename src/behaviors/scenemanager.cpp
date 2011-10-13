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
void SceneBehavior::update()
{
	u32 dt = _pFPSCounter->getValue<FPSCounter*>()->getDT();
	_pWorld->getScene().update(dt);
}
//----------------------------------------------------------------------------//
Behavior* SceneBehavior::clone() const
{
	return new SceneBehavior;
}
//----------------------------------------------------------------------------//
void SceneBehavior::added()
{
	_pWorld->getScene().added(_pOwner);
}
//----------------------------------------------------------------------------//
void SceneBehavior::activate()
{
	_pFPSCounter = _pOwner->getAttribute("fpscounter");
}
//----------------------------------------------------------------------------//
void SceneBehavior::removed()
{
	_pWorld->getScene().removed();
}
//----------------------------------------------------------------------------//
