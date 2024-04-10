#include "util/fpscounter.h"
//----------------------------------------------------------------------------//
#include <SFML/System.hpp>
//----------------------------------------------------------------------------//
using namespace he;
//----------------------------------------------------------------------------//
static sf::Clock s_clock;
//----------------------------------------------------------------------------//
FPSCounter::FPSCounter(u32 maxFramerate)
: _fps(0)
, _dt(0)
, _maxFramerate(maxFramerate)
, _lastFrameTime(0)
, _lastSecondTime(0)
, _frameCount(0)
{
	// ...
}
//----------------------------------------------------------------------------//
void FPSCounter::tick()
{
	u32 currentTime = s_clock.getElapsedTime().asMilliseconds();

	// Compute DT (time elapsed between frames)
	_dt = currentTime - _lastFrameTime;

	if (_maxFramerate > 0)
	{
		u32 maxDT = 1000 / _maxFramerate;
		if (_dt < maxDT)
		{
			sf::sleep(sf::milliseconds(maxDT - _dt));
			currentTime = s_clock.getElapsedTime().asMilliseconds();
			_dt = currentTime - _lastFrameTime;
		}
	}

	// Compute FPS
	++_frameCount;
	u32 timeSinceLastSecond = currentTime - _lastSecondTime;
	if (timeSinceLastSecond > 1000)
	{
		_fps = _frameCount;
		_frameCount = 0;
		_lastSecondTime = currentTime;
	}

	_lastFrameTime = currentTime;
}
//----------------------------------------------------------------------------//
