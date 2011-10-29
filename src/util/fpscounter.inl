//----------------------------------------------------------------------------//
inline u32 FPSCounter::getFPS() const
{
	return _fps;
}
//----------------------------------------------------------------------------//
inline u32 FPSCounter::getDT() const
{
	return _dt;
}
//----------------------------------------------------------------------------//
inline void FPSCounter::setMaxFramerate(u32 maxFramerate)
{
	_maxFramerate = maxFramerate;
}
//----------------------------------------------------------------------------//
inline u32 FPSCounter::getMaxFramerate() const
{
	return _maxFramerate;
}
//----------------------------------------------------------------------------//
