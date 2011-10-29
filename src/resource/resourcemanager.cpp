#include "resource/resourcemanager.h"
//----------------------------------------------------------------------------//
#include "core/Assert.h"
//----------------------------------------------------------------------------//
using namespace he;
//----------------------------------------------------------------------------//
void ResourceManager::addResourcePack(const std::string &name)
{
	resPacks_[name].load(name);
}
//----------------------------------------------------------------------------//
void ResourceManager::removeResourcePack(const std::string &name)
{
	resPacks_.erase(name);
}
//----------------------------------------------------------------------------//
ResourcePack& ResourceManager::getResourcePack(const std::string &name)
{
	Assert(resPacks_.find(name) != resPacks_.end(),
		   "ResourcePack not found");
	return resPacks_[name];
}
//----------------------------------------------------------------------------//
