#ifndef HE_MATHUTIL_H
#define HE_MATHUTIL_H
//----------------------------------------------------------------------------//
#include <cmath>
#include "DllExport.h"
//----------------------------------------------------------------------------//
#include "core/Types.h"
//----------------------------------------------------------------------------//
namespace he {
//----------------------------------------------------------------------------//
namespace MathUtil {
//----------------------------------------------------------------------------//
const f32 PI = 3.14159265f;
const f32 e = 2.71828183f;

template <typename Real>
Real degToRad(Real degrees)
{
	return degrees * 0.0174532925;
}

template <typename Real>
Real radToDeg(Real radians)
{
	return radians * 57.2957795;
}

template <typename Real>
void rotatePoint(Vector2<Real>& point, const f32 angle)
{
	f32 angleRad = degToRad(angle);
	f32 cos = std::cos(angleRad);
	f32 sin = std::sin(angleRad);

	Vector2<Real> temp(point);
	point.x = (cos * temp.x) - (sin * temp.y);
	point.y = (sin * temp.x) + (cos * temp.y);
}
//----------------------------------------------------------------------------//
} // end namespace MathUtil
//----------------------------------------------------------------------------//
} // end namespace he
//----------------------------------------------------------------------------//
#endif // HE_MATHUTIL_H
