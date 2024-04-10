#include "util/profile.h"
//----------------------------------------------------------------------------//
#include <sstream>
#include <algorithm>
#include <SFML/System.hpp> // for the clock functionality
//----------------------------------------------------------------------------//
#include "util/logger.h"
//----------------------------------------------------------------------------//
using namespace he;
//----------------------------------------------------------------------------//
Profiler::ProfileInfoMap Profiler::_infos;
Logger* Profiler::_logger = 0;
//----------------------------------------------------------------------------//
static sf::Clock s_clock;
//----------------------------------------------------------------------------//
void Profiler::begin(const char* name)
{
	if (!_logger)
	{
		// create for the first time
		_logger = new Logger("ProfilerLog.txt");
	}
	ProfileInfo& info = _infos[name];
	info.lastTicks = s_clock.getElapsedTime().asMilliseconds();
	++info.count;
}
//----------------------------------------------------------------------------//
void Profiler::end(const char* name)
{
	ProfileInfo& info = _infos[name];
	info.ticks += s_clock.getElapsedTime().asMilliseconds() - info.lastTicks;
}
//----------------------------------------------------------------------------//
void Profiler::clear(const char* name)
{
	using std::stringstream;

	ProfileInfo& info = _infos[name];
	stringstream ss;
	ss << "ProfileInfo [" << name << "]: "
		<< info.ticks << " / " << info.count << " : "
		<< (f32)info.ticks/(f32)info.count;
	_logger->log(ss.str().c_str());
	info.ticks = 0;
	info.count = 0;
}
//----------------------------------------------------------------------------//
void Profiler::clearAll()
{
	ProfileInfoMap::iterator it = _infos.begin();
	for (; it != _infos.end(); ++it)
	{
		Profiler::clear(it->first.c_str());
	}
	delete _logger;
	_logger = 0;
}
//----------------------------------------------------------------------------//
ProfilerBlock::ProfilerBlock(const char* name)
: _name(name)
{
	PROFILE_BEGIN(name);
}
//----------------------------------------------------------------------------//
ProfilerBlock::~ProfilerBlock()
{
	PROFILE_END(_name.c_str());
}
//----------------------------------------------------------------------------//
