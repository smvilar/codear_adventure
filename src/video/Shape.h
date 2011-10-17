#ifndef HE_SHAPE_H
#define HE_SHAPE_H
//----------------------------------------------------------------------------//
#include "DllExport.h"
#include "core/Entity.h"
#include "video/Renderer.h"
//----------------------------------------------------------------------------//
namespace he
{
//----------------------------------------------------------------------------//
class Renderer;
//----------------------------------------------------------------------------//
class ENGINE_API Shape
	: public View
{
public:
	enum ShapeType
	{
		SHAPE_TYPE_RECT,
		SHAPE_TYPE_TRI,
		SHAPE_TYPE_CIRCLE,
		SHAPE_TYPE_COUNT
	};

public:
	Shape(ShapeType shapeType = SHAPE_TYPE_RECT);
	~Shape();

	ShapeType getShapeType() const;
	void setShapeType(ShapeType shapeType);

	virtual void update();
	virtual void render(Renderer& renderer);

	virtual const Vector2f& getSize() const { return Vector2f::ZERO; }

private:
	ShapeType _shapeType;
};
//----------------------------------------------------------------------------//
} // end namespace he
//----------------------------------------------------------------------------//
#endif // HE_SHAPE_H
