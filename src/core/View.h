#ifndef HE_VIEW_H
#define HE_VIEW_H
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
// Base class for every drawable entity to be placed in a game Scene
// It contains information about its position, transform, etc.
//----------------------------------------------------------------------------//
class ENGINE_API View : public BaseObject
{
public:
	View() : _angle(0), _scale(1, 1) {}
	virtual ~View() {}

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
	f32			_angle;
	Vector2f		_scale;
};
//----------------------------------------------------------------------------//
#include "View.inl"
//----------------------------------------------------------------------------//
} // end namespace he
//----------------------------------------------------------------------------//
#endif // HE_VIEW_H
