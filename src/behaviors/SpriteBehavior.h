#ifndef FORAGERS_SPRITEBEHAVIOR_H
#define FORAGERS_SPRITEBEHAVIOR_H
//----------------------------------------------------------------------------//
#include <string>
#include "DllExport.h"
#include "core/Types.h"
#include "gameobject/gobehavior.h"
#include "video/Sprite.h"
//----------------------------------------------------------------------------//
namespace foragers {
//----------------------------------------------------------------------------//
class GOAttribute;
//----------------------------------------------------------------------------//
class ENGINE_API SpriteBehavior : public GOBehavior
{
public:
	virtual ~SpriteBehavior() {}

	virtual void update();
	//virtual void handleMessage(const char* message, void* args) {}

	virtual GOBehavior* clone() const;

protected:
	virtual void added();
	virtual void removed();
	virtual void activate();
	virtual void deactivate();

private:
	Sprite _sprite;
	GOAttribute *_posX, *_posY, *_rotation, *_scale;
};
//----------------------------------------------------------------------------//
} // end namespace foragers
//----------------------------------------------------------------------------//
#endif // FORAGERS_SPRITEBEHAVIOR_H
