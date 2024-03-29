#include "resource/resourcepack.h"
//----------------------------------------------------------------------------//
#ifdef __MAC_OS_X_VERSION_MIN_REQUIRED
#include <CoreFoundation/CoreFoundation.h>
#endif __MAC_OS_X_VERSION_MIN_REQUIRED
#include <iostream>
#include <fstream>
//----------------------------------------------------------------------------//
#include "core/assert.h"
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
#ifdef __MAC_OS_X_VERSION_MIN_REQUIRED
	CFBundleRef bundle = CFBundleGetMainBundle();
	CFStringRef location = CFStringCreateWithBytes(kCFAllocatorDefault,
												   (const UInt8*)filename.c_str(),
												   filename.size(),
												   kCFStringEncodingUTF8,
												   false); // this is for BOM checking

	CFURLRef fileUrl = CFBundleCopyResourceURL(bundle, location, NULL, NULL);
	CFRelease(location);

	// open the file in the bundle
	const size_t BUF_SIZE = 256;
	char buf[BUF_SIZE];
	CFURLGetFileSystemRepresentation(fileUrl, true, (UInt8*)buf, BUF_SIZE);
	CFRelease(fileUrl);

	std::ifstream ifs(buf, std::ios::binary);
#else
	std::ifstream ifs(filename.c_str(), std::ios::binary);
#endif

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

		std::cout << "ResourcePack: added " << filename << std::endl;
		resMap_[filename] = ResourceData(packedData, dataSize);
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
ResourceData ResourcePack::getResource(const std::string &name) const
{
	ResourceMap::const_iterator it = resMap_.find(name);
	if (it != resMap_.end())
		return it->second;
	else
		return ResourceData();
}
//----------------------------------------------------------------------------//
std::string ResourcePack::getTextResource(const std::string &name) const
{
	ResourceData res = getResource(name);
	Assert(res.data, "Resource data shouldn't be null");
	return std::string(res.data);
}
//----------------------------------------------------------------------------//
