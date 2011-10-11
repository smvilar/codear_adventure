#ifndef FORAGERS_LOGGER_H
#define FORAGERS_LOGGER_H
//----------------------------------------------------------------------------//
#include <string>
//----------------------------------------------------------------------------//
#include "DllExport.h"
#include "core/Types.h"
//----------------------------------------------------------------------------//
namespace he
{
//----------------------------------------------------------------------------//
class ENGINE_API Logger
{
public:
	Logger(const char* filename = "");
	~Logger();

	void log(const char* message, u8 level = 0);

	// the level is 0 from default, allowing messages of level 0 or greater
	void setLevel(u8 level);
	u8 getLevel() const;

private:
	std::string		_filename;
	u8				_currentLevel;
	bool			_firstLog;

	void printHeader() const;
	void printFooter() const;
	void printInFile(const char* message) const;
};
//----------------------------------------------------------------------------//
#include "Logger.inl"
//----------------------------------------------------------------------------//
} // end namespace he
//----------------------------------------------------------------------------//
#endif // FORAGERS_LOGGER_H
//----------------------------------------------------------------------------//
