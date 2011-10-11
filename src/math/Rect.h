#ifndef FORAGERS_RECT_H
#define FORAGERS_RECT_H
//----------------------------------------------------------------------------//
#include <cmath>
#include "core/Types.h"
#include "Vector2.h"
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
	// Parameterized constructor
	Rect(const Vector2<Real>& topLeft, const Vector2<Real>& bottomRight);
	// Copy constructor
	Rect(const Rect& other);
	// Destructor
	~Rect();

	Real getWidth() const;
	Real getHeight() const;
};
//----------------------------------------------------------------------------//
#include "Rect.inl"
//----------------------------------------------------------------------------//
typedef Rect<f32> Rectf;
typedef Rect<f64> Rectd;
typedef Rect<u32> Rectu;
typedef Rect<s32> Recti;
//----------------------------------------------------------------------------//
} // end namespace he
//----------------------------------------------------------------------------//
#endif // FORAGERS_RECT_H
