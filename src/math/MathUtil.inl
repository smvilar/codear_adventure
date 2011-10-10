//----------------------------------------------------------------------------//
inline float MathUtil::degToRad(float degrees)
{
	return degrees * 0.0174532925f;
}
//----------------------------------------------------------------------------//
inline float MathUtil::radToDeg(float radians)
{
	return radians * 57.2957795f;
}
//----------------------------------------------------------------------------//
template <typename Real>
inline void MathUtil::rotatePoint(Vector2<Real>& point, const f32 angle)
{
	f32 angleRad = degToRad(angle);
	f32 cos = std::cos(angleRad);
	f32 sin = std::sin(angleRad);
	
	Vector2<Real> temp(point);
	point.x = (cos * temp.x) - (sin * temp.y);
	point.y = (sin * temp.x) + (cos * temp.y);
}
//----------------------------------------------------------------------------//
