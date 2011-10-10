#ifndef FORAGERS_RESOURCEMANAGER_H
#define FORAGERS_RESOURCEMANAGER_H
//----------------------------------------------------------------------------//
#include <map>
//----------------------------------------------------------------------------//
#include "resource/IResource.h"
//----------------------------------------------------------------------------//
namespace foragers
{
//----------------------------------------------------------------------------//
class Texture;
//----------------------------------------------------------------------------//
// Creates and stores resources, using boost::shared_ptr to have an automatic
// reference counting system.
//----------------------------------------------------------------------------//
class ENGINE_API ResourceManager
{
public:
	ResourceManager();
	~ResourceManager();

	void removeUnusedResources();
	u32 getLoadedCount() const;

	// Returns a resource with that name,
	// if it doesn't exists, it tries to load it from a file
	template <class ResType>
	boost::shared_ptr<ResType> get(const char* name);

	// adds a resource to the manager
	template <class ResType>
	boost::shared_ptr<ResType> add(const char* name, ResType* res);
	
private:
	typedef std::map<const char*, IResourcePtr> ResourceMap;
	ResourceMap _resMap;
};
//----------------------------------------------------------------------------//
#include "ResourceManager.inl"
//----------------------------------------------------------------------------//
} // end namespace foragers
//----------------------------------------------------------------------------//
#endif // FORAGERS_RESOURCEMANAGER_H
