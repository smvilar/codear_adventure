#ifndef HE_RECT_H
#define HE_RECT_H
//----------------------------------------------------------------------------//
#include <cmath>
//----------------------------------------------------------------------------//
#include "core/types.h"
#include "math/vector2.h"
//----------------------------------------------------------------------------//
namespace he
{
//----------------------------------------------------------------------------//
template <typename Real>
class Rect
{
public:
	Vector2<Real> topLeft;
	Vector2<Real> bottomRight;

	// Default constructor
	Rect();
	// Parameterized constructors
	Rect(const Vector2<Real>& topLeft, const Vector2<Real>& bottomRight);
	Rect(Real x, Real y, Real width, Real height);
	// Copy constructor
	Rect(const Rect& other);
	// Destructor
	~Rect();

	Real getWidth() const;
	Real getHeight() const;

	bool contains(const Vector2<Real>& point);
};
//----------------------------------------------------------------------------//
#include "rect.inl"
//----------------------------------------------------------------------------//
typedef Rect<f32> Rectf;
typedef Rect<f64> Rectd;
typedef Rect<u32> Rectu;
typedef Rect<s32> Recti;
//----------------------------------------------------------------------------//
} // end namespace he
//----------------------------------------------------------------------------//
#endif // HE_RECT_H
