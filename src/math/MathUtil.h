#ifndef HE_MATHUTIL_H
#define HE_MATHUTIL_H
//----------------------------------------------------------------------------//
#include <cmath>
#include "DllExport.h"
//----------------------------------------------------------------------------//
#include "core/Types.h"
//----------------------------------------------------------------------------//
namespace he
{
//----------------------------------------------------------------------------//
template <typename Real>
class Vector2;
//----------------------------------------------------------------------------//
class ENGINE_API MathUtil
{
public:
	static const f32 PI;
	static const f32 e;

	static f32 degToRad(f32 degrees);
	static f32 radToDeg(f32 radians);

	template <typename Real>
	static void rotatePoint(Vector2<Real>& point, const f32 angle);

private:
	// not really meant to be instantiated
	MathUtil() {}
	MathUtil(const MathUtil&) {}
	MathUtil& operator=(const MathUtil&) { return *this; }
};
//----------------------------------------------------------------------------//
#include "MathUtil.inl"
//----------------------------------------------------------------------------//
} // end namespace he
//----------------------------------------------------------------------------//
#endif // HE_MATHUTIL_H
