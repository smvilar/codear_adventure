#include "resource/resourcemanager.h"
//----------------------------------------------------------------------------//
using namespace he;
//----------------------------------------------------------------------------//
void ResourceManager::addResourcePack(const std::string &name)
{
	resPacks_[name].load(name);
	if (!defaultResPack_)
		defaultResPack_ = &resPacks_[name];
}
//----------------------------------------------------------------------------//
void ResourceManager::removeResourcePack(const std::string &name)
{
	Assert(resPacks_.find(name) != resPacks_.end(),
		   "ResourcePack not found");
	if (defaultResPack_ == &resPacks_[name])
		defaultResPack_ = 0;
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
void ResourceManager::setDefaultResourcePack(const std::string &name)
{
	Assert(resPacks_.find(name) != resPacks_.end(),
		   "ResourcePack not found");
	defaultResPack_ = &resPacks_[name];
}
//----------------------------------------------------------------------------//
