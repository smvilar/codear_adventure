#include "util/Logger.h"
#include <iostream>
#include <fstream>
#include <ctime>
//----------------------------------------------------------------------------//
using namespace he;
//----------------------------------------------------------------------------//
Logger::Logger(const char* filename)
: _filename(filename)
, _currentLevel(0)
, _firstLog(true)
{
}
//----------------------------------------------------------------------------//
Logger::~Logger()
{
	printFooter();
}
//----------------------------------------------------------------------------//
void Logger::log(const char* message, u8 level)
{
	bool hasFile = !_filename.empty();

	if (_firstLog)
	{
		_firstLog = false;
		if (hasFile)
		{
			printHeader();
		}
	}

	if (hasFile)
	{
		printInFile(message);
	}

	if (level >= _currentLevel)
	{
		std::cout << message << std::endl;
	}
}
//----------------------------------------------------------------------------//
void Logger::printHeader() const
{
	time_t curTime;
	time(&curTime);
	std::fstream fs;
	fs.open(_filename.c_str(), std::ios::out|std::ios::app);
	fs	<< std::endl
		<< "=================================================" << std::endl
		<< "Engine Log File" << std::endl
		<< ctime(&curTime)
		<< "=================================================" << std::endl
		<< std::endl;
	fs.close();
}
//----------------------------------------------------------------------------//
void Logger::printFooter() const
{
	time_t curTime;
	time(&curTime);
	std::fstream fs;
	fs.open(_filename.c_str(), std::ios::out|std::ios::app);
	fs	<< std::endl
		<< "=================================================" << std::endl
		<< "End of Log File" << std::endl
		<< ctime(&curTime)
		<< "=================================================" << std::endl
		<< std::endl;
	fs.close();
}
//----------------------------------------------------------------------------//
void Logger::printInFile(const char* message) const
{
	std::fstream fs;
	fs.open(_filename.c_str(), std::ios::out|std::ios::app);
	fs	<< message << std::endl;
	fs.close();
}
//----------------------------------------------------------------------------//
