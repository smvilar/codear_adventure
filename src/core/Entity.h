#ifndef FORAGERS_ENTITY_H
#define FORAGERS_ENTITY_H
//----------------------------------------------------------------------------//
#include "BaseObject.h"
#include "math/Vector2.h"
//----------------------------------------------------------------------------//
namespace he
{
//----------------------------------------------------------------------------//
class Renderer;
class World;
//----------------------------------------------------------------------------//
// Base class for every entity to be placed in a game Scene
// It contains information about its position, transform, etc.
//----------------------------------------------------------------------------//
class ENGINE_API Entity
	: public BaseObject
{
public:
	Entity()
		: _angle(0),
		_scale(1, 1) {}
	virtual ~Entity() {}

public:
	virtual void update(u32 elapsedMs) = 0;
	virtual void render(Renderer& renderer) = 0;

public:
	void setPosition(const Vector2f& position);
	void setAngle(const f32 angle);
	void setScale(const Vector2f& scale);

	const Vector2f& getPosition() const;
	f32 getAngle() const;
	const Vector2f& getScale() const;

	virtual const Vector2f& getSize() const = 0;

protected:
	Vector2f		_position;
	f32				_angle;
	Vector2f		_scale;
};
//----------------------------------------------------------------------------//
#include "Entity.inl"
//----------------------------------------------------------------------------//
} // end namespace he
//----------------------------------------------------------------------------//
#endif // FORAGERS_ENTITY_H
