#ifndef FORAGERS_SCENEBEHAVIOR_H
#define FORAGERS_SCENEBEHAVIOR_H
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

private:
	Attribute *_pFPSCounter;
};
//----------------------------------------------------------------------------//
} // end namespace he
//----------------------------------------------------------------------------//
#endif // FORAGERS_SCENEBEHAVIOR_H
