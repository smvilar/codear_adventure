#ifndef FORAGERS_SPRITEBEHAVIOR_H
#define FORAGERS_SPRITEBEHAVIOR_H
//----------------------------------------------------------------------------//
#include <string>
#include "DllExport.h"
#include "core/Types.h"
#include "gameobject/behavior.h"
#include "video/Sprite.h"
//----------------------------------------------------------------------------//
namespace he {
//----------------------------------------------------------------------------//
class Attribute;
//----------------------------------------------------------------------------//
class ENGINE_API SpriteBehavior : public Behavior
{
public:
	virtual ~SpriteBehavior() {}

	virtual void update();

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
} // end namespace he
//----------------------------------------------------------------------------//
#endif // FORAGERS_SPRITEBEHAVIOR_H
