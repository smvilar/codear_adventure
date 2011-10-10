#ifndef FORAGERS_PROFILE_H
#define FORAGERS_PROFILE_H
//----------------------------------------------------------------------------//
#include <string>
#include <map>
//----------------------------------------------------------------------------//
#include "DllExport.h"
#include "core/Types.h"
//----------------------------------------------------------------------------//
namespace foragers
{
class Logger;
//----------------------------------------------------------------------------//
class ENGINE_API Profiler
{
	struct ProfileInfo
	{
		u32 lastTicks;
		u32 ticks;
		u32 count;
	};

	typedef std::map<std::string, ProfileInfo> ProfileInfoMap;
	static ProfileInfoMap _infos;
	static Logger* _logger;

public:
	static void begin(const char* name);
	static void end(const char* name);
	static void clear(const char* name);

	static void clearAll();
};
//----------------------------------------------------------------------------//
#define PROFILER_ENABLED 1
#if PROFILER_ENABLED
#define PROFILE_BEGIN(name) Profiler::begin(name)
#define PROFILE_END(name) Profiler::end(name)
#define PROFILE_CLEAR(name) Profiler::clear(name)
#else // PROFILER_ENABLED
#define PROFILE_BEGIN(name)
#define PROFILE_END(name)
#define PROFILE_CLEAR(name)
#endif // PROFILER_ENABLED
//----------------------------------------------------------------------------//
class ENGINE_API ProfilerBlock
{
	std::string _name;
public:
	ProfilerBlock(const char* name);
	~ProfilerBlock();
};
//----------------------------------------------------------------------------//
} // end namespace foragers
//----------------------------------------------------------------------------//
#endif // FORAGERS_PROFILE_H
//----------------------------------------------------------------------------//
