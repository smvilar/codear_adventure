#include "util/resourcepack.h"
//----------------------------------------------------------------------------//
#include <iostream>
#include <fstream>
//----------------------------------------------------------------------------//
using namespace he;
//----------------------------------------------------------------------------//
ResourcePack::ResourcePack()
: loaded_(false)
{
}
//----------------------------------------------------------------------------//
ResourcePack::~ResourcePack()
{
	unload();
}
//----------------------------------------------------------------------------//
bool ResourcePack::load(const std::string &filename)
{
	std::ifstream ifs(filename.c_str(), std::ios::binary);
	if (!ifs.is_open())
	{
		std::cerr << "Error opening ResourcePack: " << filename << std::endl;
		return false;
	}

	while (ifs.good())
	{
		// get the filename
		const size_t TEMP_BUFFER_SIZE = 512;
		char filename[TEMP_BUFFER_SIZE];
		ifs.getline(filename, TEMP_BUFFER_SIZE);
		if (ifs.eof()) break;
		// now get the filesize
		int dataSize;
		ifs.read((char*)&dataSize, sizeof(dataSize));
		// now get the packed data! this pointer gets deleted in the dtor
		char *packedData = new char[dataSize];
		ifs.read(packedData, dataSize);

		resMap_[filename] = Resource(packedData, dataSize);
	}

	loaded_ = true;

	return true;
}
//----------------------------------------------------------------------------//
void ResourcePack::unload()
{
	ResourceMap::iterator it = resMap_.begin();
	for (; it != resMap_.end(); ++it)
	{
		delete [] it->second.data;
	}
	resMap_.clear();

	loaded_ = false;
}
//----------------------------------------------------------------------------//
ResourcePack::Resource ResourcePack::getResource(const std::string &name) const
{
	ResourceMap::const_iterator it = resMap_.find(name);
	if (it != resMap_.end())
		return it->second;
	else
		return Resource();
}
//----------------------------------------------------------------------------//
std::string ResourcePack::getTextResource(const std::string &name) const
{
	Resource res = getResource(name);
	return std::string(res.data);
}
//----------------------------------------------------------------------------//
