#ifndef HE_SCENEMANAGER_H
#define HE_SCENEMANAGER_H
//----------------------------------------------------------------------------//
#include <stack>
//----------------------------------------------------------------------------//
#include "DllExport.h"
#include "gameobject/behavior.h"
//----------------------------------------------------------------------------//
namespace he {
//----------------------------------------------------------------------------//
class Scene;
class Attribute;
//----------------------------------------------------------------------------//
class ENGINE_API SceneBehavior : public Behavior
{
public:
	virtual void update();
	virtual Behavior* clone() const;

private:
	virtual void added();
	virtual void activate();

	virtual void removed();

private:
	Attribute *_pFPSCounter;
};
//----------------------------------------------------------------------------//
} // end namespace he
//----------------------------------------------------------------------------//
#endif // HE_SCENEMANAGER_H
