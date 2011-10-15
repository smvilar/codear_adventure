//----------------------------------------------------------------------------//
template <typename Real>
inline Rect<Real>::Rect()
{
	// lightweight
}
//----------------------------------------------------------------------------//
template <typename Real>
inline Rect<Real>::Rect(const Vector2<Real>& topLeft,
						const Vector2<Real>& bottomRight)
: topLeft(topLeft)
, bottomRight(bottomRight)
{
	// ...
}
//----------------------------------------------------------------------------//
template <typename Real>
inline Rect<Real>::Rect(Real x, Real y, Real width, Real height)
: topLeft(x, y)
, bottomRight(x + width, y + height)
{
	// ...
}
//----------------------------------------------------------------------------//
template <typename Real>
inline Rect<Real>::Rect(const Rect& other)
: topLeft(other.topLeft)
, bottomRight(other.bottomRight)
{
	// ...
}
//----------------------------------------------------------------------------//
template <typename Real>
inline Rect<Real>::~Rect()
{
	// ...
}
//----------------------------------------------------------------------------//
template <typename Real>
inline Real Rect<Real>::getWidth() const
{
	return abs(bottomRight.x - topLeft.x);
}
//----------------------------------------------------------------------------//
template <typename Real>
inline Real Rect<Real>::getHeight() const
{
	return abs(bottomRight.x - topLeft.x);
}
//----------------------------------------------------------------------------//
template <typename Real>
inline bool Rect<Real>::contains(const Vector2<Real>& point)
{
	if (point.x < topLeft.x) return false;
	if (point.x > bottomRight.x) return false;
	if (point.y < topLeft.y) return false;
	if (point.y > bottomRight.y) return false;
	return true;
}
//----------------------------------------------------------------------------//
