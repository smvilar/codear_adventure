#ifndef HE_RESOURCEMANAGER_H
#define HE_RESOURCEMANAGER_H
//----------------------------------------------------------------------------//
#include "dllexport.h"
#include "core/assert.h"
#include "resource/resourcepack.h"
//----------------------------------------------------------------------------//
namespace he {
//----------------------------------------------------------------------------//
class ENGINE_API ResourceManager
{
public:
	ResourceManager() : defaultResPack_(0) {}

	void addResourcePack(const std::string &name);
	void removeResourcePack(const std::string &name);
	ResourcePack& getResourcePack(const std::string &name);

	// Sets the default Resource Pack
	// Every following call to 'getResource' will use this
	void setDefaultResourcePack(const std::string &name);
	ResourcePack& getDefaultResourcePack() const;

	ResourceData getResource(const std::string &name) const;
	std::string getTextResource(const std::string &name) const;

private:
	typedef std::map<std::string, ResourcePack> ResourcePackMap;
	ResourcePackMap resPacks_;

	ResourcePack *defaultResPack_;
};
//----------------------------------------------------------------------------//
inline ResourcePack& ResourceManager::getDefaultResourcePack() const
{
	Assert(defaultResPack_, "defaultResPack shouldn't be null");
	return *defaultResPack_;
}
//----------------------------------------------------------------------------//
inline ResourceData ResourceManager::getResource(const std::string &name) const
{
	Assert(defaultResPack_, "defaultResPack shouldn't be null");
	return defaultResPack_->getResource(name);
}
//----------------------------------------------------------------------------//
inline std::string ResourceManager::getTextResource(const std::string &name) const
{
	Assert(defaultResPack_, "defaultResPack shouldn't be null");
	return defaultResPack_->getTextResource(name);
}
//----------------------------------------------------------------------------//
} // end namespace he
//----------------------------------------------------------------------------//
#endif // HE_RESOURCEMANAGER_H
