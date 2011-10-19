#ifndef HE_SPRITEBEHAVIOR_H
#define HE_SPRITEBEHAVIOR_H
//----------------------------------------------------------------------------//
#include <string>
//----------------------------------------------------------------------------//
#include <SFML/Graphics.hpp>
//----------------------------------------------------------------------------//
#include "DllExport.h"
#include "core/Types.h"
#include "gameobject/behavior.h"
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
	sf::Sprite _sprite;
	Attribute *_posX, *_posY, *_rotation, *_scale;
};
//----------------------------------------------------------------------------//
} // end namespace he
//----------------------------------------------------------------------------//
#endif // HE_SPRITEBEHAVIOR_H
