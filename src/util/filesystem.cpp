#include "util/filesystem.h"
//----------------------------------------------------------------------------//
#include <iostream>
#include <fstream>
#include <sstream>
//----------------------------------------------------------------------------//
using namespace he;
//----------------------------------------------------------------------------//
FileSystem::PathArray FileSystem::s_paths;
//----------------------------------------------------------------------------//
void FileSystem::addPath(const char* path)
{
	for (size_t i=0; i<s_paths.size(); ++i)
	{
		if (s_paths[i] == path)
		{
			std::clog << "FileSystem::AddPath: path already added." << std::endl;
			return;
		}
	}
	s_paths.push_back(path);
}
//----------------------------------------------------------------------------//
void FileSystem::removePath(const char* path)
{
	for (size_t i=0; i<s_paths.size(); ++i)
	{
		if (s_paths[i] == path)
		{
			s_paths[i] = s_paths[s_paths.size()-1];
			s_paths.pop_back();
			return;
		}
	}
	std::clog << "FileSystem::RemovePath: path not found." << std::endl;
}
//----------------------------------------------------------------------------//
bool FileSystem::fileExists(const char* filename)
{
	std::ifstream ifs;
	ifs.open(filename, std::ios::in);
	if (!ifs.is_open())
	{
		std::stringstream ss;
		for (size_t i=0; i<s_paths.size(); ++i)
		{
			ss << s_paths[i] << filename;
			ifs.open(ss.str().c_str(), std::ios::in);
			if (!ifs.fail())
			{
				ifs.close();
				return true;
			}
			ss.clear();
		}
	}
	else
	{
		ifs.close();
		return true;
	}

	return false;
}
//----------------------------------------------------------------------------//
