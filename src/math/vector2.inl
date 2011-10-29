//----------------------------------------------------------------------------//
template <typename Real>
Vector2<Real>::Vector2()
{
	// lightweight
}
//----------------------------------------------------------------------------//
template <typename Real>
Vector2<Real>::Vector2(Real x, Real y)
: x(x)
, y(y)
{
	// ...
}
//----------------------------------------------------------------------------//
template <typename Real>
Vector2<Real>::Vector2(Real xy)
: x(xy)
, y(xy)
{
	// ...
}
//----------------------------------------------------------------------------//
template <typename Real>
Vector2<Real>::Vector2(const Vector2<Real>& other)
: x(other.x)
, y(other.y)
{
	// ...
}
//----------------------------------------------------------------------------//
template <typename Real>
Vector2<Real>::~Vector2()
{
	// ...
}
//----------------------------------------------------------------------------//
template <typename Real>
Vector2<Real>& Vector2<Real>::operator=(const Vector2& other)
{
	x = other.x;
	y = other.y;

	return *this;
}
//----------------------------------------------------------------------------//
template <typename Real>
Vector2<Real> Vector2<Real>::operator+(const Vector2& other) const
{
	return Vector2<Real>(x + other.x, y + other.y);
}
//----------------------------------------------------------------------------//
template <typename Real>
Vector2<Real> Vector2<Real>::operator-(const Vector2& other) const
{
	return Vector2<Real>(x - other.x, y - other.y);
}
//----------------------------------------------------------------------------//
template <typename Real>
Vector2<Real> Vector2<Real>::operator*(const Real& scalar) const
{
	return Vector2<Real>(x * scalar, y * scalar);
}
//----------------------------------------------------------------------------//
template <typename Real>
Vector2<Real> Vector2<Real>::operator/(const Real& scalar) const
{
	Real invScalar = (Real)1.0 / scalar;
	return Vector2<Real>(x * invScalar, y * invScalar);
}
//----------------------------------------------------------------------------//
template <typename Real>
Vector2<Real> Vector2<Real>::operator-() const
{
	return Vector2<Real>(-x, -y);
}
//----------------------------------------------------------------------------//
template <typename Real>
Vector2<Real>& Vector2<Real>::operator+=(const Vector2& other)
{
	x += other.x;
	y += other.y;

	return *this;
}
//----------------------------------------------------------------------------//
template <typename Real>
Vector2<Real>& Vector2<Real>::operator-=(const Vector2& other)
{
	x -= other.x;
	y -= other.y;

	return *this;
}
//----------------------------------------------------------------------------//
template <typename Real>
Vector2<Real>& Vector2<Real>::operator*=(const Real& scalar)
{
	x *= scalar;
	y *= scalar;

	return *this;
}
//----------------------------------------------------------------------------//
template <typename Real>
Vector2<Real>& Vector2<Real>::operator/=(const Real& scalar)
{
	Real invScalar = (Real)1.0 / scalar;
	x *= invScalar;
	y *= invScalar;

	return *this;
}
//----------------------------------------------------------------------------//
template <typename Real>
bool Vector2<Real>::operator==(const Vector2& other) const
{
	return x == other.x && y == other.y;
}
//----------------------------------------------------------------------------//
template <typename Real>
Real Vector2<Real>::getMagnitude() const
{
	return sqrt(x * x + y * y);
}
//----------------------------------------------------------------------------//
template <typename Real>
Real Vector2<Real>::getMagnitudeSq() const
{
	return (x * x + y * y);
}
//----------------------------------------------------------------------------//
template <typename Real>
Vector2<Real>& Vector2<Real>::normalize()
{
	Real invMag = (Real)1.0 / getMagnitude();
	x *= invMag;
	y *= invMag;

	return *this;
}
//----------------------------------------------------------------------------//
template <typename Real>
Vector2<Real>& Vector2<Real>::setMagnitude(const Real& scalar)
{
	Real invMag = scalar * (Real)1.0 / getMagnitude();
	x *= invMag;
	y *= invMag;

	return *this;
}
//----------------------------------------------------------------------------//
template <typename Real>
Real Vector2<Real>::dot(const Vector2<Real>& other) const
{
	return x * other.x + y * other.y;
}
//----------------------------------------------------------------------------//
template <typename Real>
Real Vector2<Real>::distance(const Vector2<Real>& other)
{
	return sqrt((x - other.x) * (x - other.x) +
		(y - other.y) * (y - other.y));
}
//----------------------------------------------------------------------------//
template <typename Real>
Real Vector2<Real>::distanceSq(const Vector2<Real>& other)
{
	return (x - other.x) * (x - other.x) +
		(y - other.y) * (y - other.y);
}
//----------------------------------------------------------------------------//
template <typename Real>
void Vector2<Real>::toArray(Real* outArray) const
{
	Assert(outArray, "Vector2::ToArray(): outArray is NULL!");
	outArray[0] = x;
	outArray[1] = y;
}
//----------------------------------------------------------------------------//
