#ifndef HE_RESOURCEPACK_H
#define HE_RESOURCEPACK_H
//----------------------------------------------------------------------------//
#include <string>
#include <map>
//----------------------------------------------------------------------------//
#include "dllexport.h"
//----------------------------------------------------------------------------//
namespace he {
//----------------------------------------------------------------------------//
class ENGINE_API ResourcePack
{
public:
	ResourcePack();
	~ResourcePack();

	struct Resource
	{
		char *data;
		size_t size;

		Resource() : data(0), size(0) {}
		Resource(char *data, size_t size) : data(data), size(size) {}
	};

public:
	bool load(const std::string &filename);
	void unload();

	Resource getResource(const std::string &name) const;

	std::string getTextResource(const std::string &name) const;

private:
	typedef std::map<std::string, Resource> ResourceMap;
	ResourceMap resMap_;

	bool loaded_;
};
//----------------------------------------------------------------------------//
} // end namespace he
//----------------------------------------------------------------------------//
#endif // HE_RESOURCEPACK_H
