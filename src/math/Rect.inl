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
