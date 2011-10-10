//----------------------------------------------------------------------------//
inline void Entity::setPosition(const Vector2f& position)
{
	_position = position;
}
//----------------------------------------------------------------------------//
inline void Entity::setAngle(const f32 angle)
{
	_angle = angle;
}
//----------------------------------------------------------------------------//
inline void Entity::setScale(const Vector2f& scale)
{
	_scale = scale;
}
//----------------------------------------------------------------------------//
inline const Vector2f& Entity::getPosition() const
{
	return _position;
}
//----------------------------------------------------------------------------//
inline f32 Entity::getAngle() const
{
	return _angle;
}
//----------------------------------------------------------------------------//
inline const Vector2f& Entity::getScale() const
{
	return _scale;
}
//----------------------------------------------------------------------------//
