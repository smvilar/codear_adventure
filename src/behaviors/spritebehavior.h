#ifndef HE_SPRITEBEHAVIOR_H
#define HE_SPRITEBEHAVIOR_H
//----------------------------------------------------------------------------//
#include "dllexport.h"
#include "core/types.h"
#include "gameobject/behavior.h"
#include "video/animatedsprite.h"
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
	virtual void activate();
	virtual void deactivate();

private:
	AnimatedSprite animatedSprite_;
	Attribute *posX_, *posY_, *rotation_, *scale_;
};
//----------------------------------------------------------------------------//
} // end namespace he
//----------------------------------------------------------------------------//
#endif // HE_SPRITEBEHAVIOR_H
