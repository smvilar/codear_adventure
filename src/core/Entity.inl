//----------------------------------------------------------------------------//
inline void View::setPosition(const Vector2f& position)
{
	_position = position;
}
//----------------------------------------------------------------------------//
inline void View::setAngle(const f32 angle)
{
	_angle = angle;
}
//----------------------------------------------------------------------------//
inline void View::setScale(const Vector2f& scale)
{
	_scale = scale;
}
//----------------------------------------------------------------------------//
inline const Vector2f& View::getPosition() const
{
	return _position;
}
//----------------------------------------------------------------------------//
inline f32 View::getAngle() const
{
	return _angle;
}
//----------------------------------------------------------------------------//
inline const Vector2f& View::getScale() const
{
	return _scale;
}
//----------------------------------------------------------------------------//
