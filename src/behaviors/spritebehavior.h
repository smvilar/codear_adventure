#ifndef FORAGERS_SPRITEBEHAVIOR_H
#define FORAGERS_SPRITEBEHAVIOR_H
//----------------------------------------------------------------------------//
#include <string>
#include "DllExport.h"
#include "core/Types.h"
#include "gameobject/behavior.h"
#include "video/Sprite.h"
//----------------------------------------------------------------------------//
namespace foragers {
//----------------------------------------------------------------------------//
class Attribute;
//----------------------------------------------------------------------------//
class ENGINE_API SpriteBehavior : public Behavior
{
public:
	virtual ~SpriteBehavior() {}

	virtual void update();
	//virtual void handleMessage(const char* message, void* args) {}

	virtual Behavior* clone() const;

protected:
	virtual void added();
	virtual void removed();
	virtual void activate();
	virtual void deactivate();

private:
	Sprite _sprite;
	Attribute *_posX, *_posY, *_rotation, *_scale;
};
//----------------------------------------------------------------------------//
} // end namespace foragers
//----------------------------------------------------------------------------//
#endif // FORAGERS_SPRITEBEHAVIOR_H
