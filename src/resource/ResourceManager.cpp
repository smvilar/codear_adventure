#include "resource/ResourceManager.h"
//----------------------------------------------------------------------------//
#include <iostream>
//----------------------------------------------------------------------------//
using namespace he;
//----------------------------------------------------------------------------//
ResourceManager::ResourceManager()
{
}
//----------------------------------------------------------------------------//
ResourceManager::~ResourceManager()
{
	removeUnusedResources();
	if (getLoadedCount() > 0)
	{
		std::cerr << "There's a resource leak!!" << std::endl;
		ResourceMap::iterator it = _resMap.begin();
		for (; it != _resMap.end(); ++it)
		{
			std::cerr << "Unreleased resource: " << it->first << std::endl;
		}
	}
}
//----------------------------------------------------------------------------//
void ResourceManager::removeUnusedResources()
{
	ResourceMap::iterator it = _resMap.begin();
	while (it != _resMap.end())
	{
		if (it->second.use_count() == 1)
		{
			// it's only referenced in the map, kill it!
			_resMap.erase(it++);
		}
		else
		{
			++it;
		}
	}
}
//----------------------------------------------------------------------------//
u32 ResourceManager::getLoadedCount() const
{
	return _resMap.size();
}
//----------------------------------------------------------------------------//
