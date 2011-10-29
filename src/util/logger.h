#ifndef HE_LOGGER_H
#define HE_LOGGER_H
//----------------------------------------------------------------------------//
#include <string>
//----------------------------------------------------------------------------//
#include "dllexport.h"
#include "core/types.h"
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
#include "logger.inl"
//----------------------------------------------------------------------------//
} // end namespace he
//----------------------------------------------------------------------------//
#endif // HE_LOGGER_H
//----------------------------------------------------------------------------//
