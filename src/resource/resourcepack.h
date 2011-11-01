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
struct ENGINE_API ResourceData
{
	char *data;
	size_t size;

	ResourceData() : data(0), size(0) {}
	ResourceData(char *data, size_t size) : data(data), size(size) {}
};
//----------------------------------------------------------------------------//
class ENGINE_API ResourcePack
{
public:
	ResourcePack();
	~ResourcePack();

public:
	bool load(const std::string &filename);
	void unload();

	ResourceData getResource(const std::string &name) const;
	std::string getTextResource(const std::string &name) const;

private:
	typedef std::map<std::string, ResourceData> ResourceMap;
	ResourceMap resMap_;

	bool loaded_;
};
//----------------------------------------------------------------------------//
} // end namespace he
//----------------------------------------------------------------------------//
#endif // HE_RESOURCEPACK_H
