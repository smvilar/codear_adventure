#ifndef FORAGERS_VECTOR2_H
#define FORAGERS_VECTOR2_H
//----------------------------------------------------------------------------//
#include <cmath>
#include "core/Types.h"
#include "core/Assert.h"
//----------------------------------------------------------------------------//
namespace foragers
{
//----------------------------------------------------------------------------//
template <typename Real>
class Vector2
{
public:
	Real x;
	Real y;

	// Default constructor
	Vector2();
	// Parameterized constructor
	Vector2(Real x, Real y);
	// A unique value for the 2 components
	explicit Vector2(Real xy);
	// Copy constructor
	Vector2(const Vector2& other);
	// Destructor
	~Vector2();

	// Assignment
	Vector2& operator=(const Vector2& other);
	// Basic operations
	Vector2 operator+(const Vector2& other) const;
	Vector2 operator-(const Vector2& other) const;
	Vector2 operator*(const Real& scalar) const;
	Vector2 operator/(const Real& scalar) const;
	Vector2 operator-() const;
	// Basic operations with assignment
	Vector2& operator+=(const Vector2& other);
	Vector2& operator-=(const Vector2& other);
	Vector2& operator*=(const Real& scalar);
	Vector2& operator/=(const Real& scalar);
	// Comparisons
	bool operator==(const Vector2& other) const;

	Real getMagnitude() const;
	Real getMagnitudeSq() const;
	Vector2& normalize();
	Vector2& setMagnitude(const Real& scalar);

	// Dot / Inner product
	Real dot(const Vector2& other) const;

	// Distance from another point
	Real distance(const Vector2& other);
	Real distanceSq(const Vector2& other);

	void toArray(Real* outArray) const;

	// Helper
	static const Vector2 ZERO;
	static const Vector2 UNIT_X;
	static const Vector2 UNIT_Y;
};
//----------------------------------------------------------------------------//
#include "Vector2.inl"
//----------------------------------------------------------------------------//
typedef Vector2<f32> Vector2f;
typedef Vector2<f64> Vector2d;
typedef Vector2<u32> Vector2u;
typedef Vector2<s32> Vector2i;
//----------------------------------------------------------------------------//
#ifdef _MSC_VER
template <> const Vector2f Vector2f::ZERO(0.0f);
template <> const Vector2f Vector2f::UNIT_X(1.0f, 0.0f);
template <> const Vector2f Vector2f::UNIT_Y(0.0f, 1.0f);
//----------------------------------------------------------------------------//
template <> const Vector2d Vector2d::ZERO(0.0);
template <> const Vector2d Vector2d::UNIT_X(1.0, 0.0);
template <> const Vector2d Vector2d::UNIT_Y(0.0, 1.0);
//----------------------------------------------------------------------------//
template <> const Vector2u Vector2u::ZERO(0);
template <> const Vector2u Vector2u::UNIT_X(1, 0);
template <> const Vector2u Vector2u::UNIT_Y(0, 1);
//----------------------------------------------------------------------------//
template <> const Vector2i Vector2i::ZERO(0);
template <> const Vector2i Vector2i::UNIT_X(1, 0);
template <> const Vector2i Vector2i::UNIT_Y(0, 1);
//----------------------------------------------------------------------------//
#endif // _MSC_VER
} // end namespace foragers
//----------------------------------------------------------------------------//
#endif // FORAGERS_VECTOR2_H
