#ifndef HE_RESOURCEMANAGER_H
#define HE_RESOURCEMANAGER_H
//----------------------------------------------------------------------------//
#include "dllexport.h"
#include "resource/resourcepack.h"
//----------------------------------------------------------------------------//
namespace he {
//----------------------------------------------------------------------------//
class ENGINE_API ResourceManager
{
public:
	void addResourcePack(const std::string &name);
	void removeResourcePack(const std::string &name);
	ResourcePack& getResourcePack(const std::string &name);

private:
	typedef std::map<std::string, ResourcePack> ResourcePackMap;
	ResourcePackMap resPacks_;
};
//----------------------------------------------------------------------------//
} // end namespace he
//----------------------------------------------------------------------------//
#endif // HE_RESOURCEMANAGER_H
