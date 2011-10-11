#ifndef HE_FILESYSTEM_H
#define HE_FILESYSTEM_H
//----------------------------------------------------------------------------//
#include <string>
#include <vector>
#include "DllExport.h"
#include "core/Types.h"
//----------------------------------------------------------------------------//
namespace he
{
//----------------------------------------------------------------------------//
class ENGINE_API FileSystem
{
public:
	static void addPath(const char* path);
	static void removePath(const char* path);
	static bool fileExists(const char* filename);

private:
	typedef std::vector<std::string> PathArray;
	static PathArray s_paths;
};
//----------------------------------------------------------------------------//
} // end namespace he
//----------------------------------------------------------------------------//
#endif // HE_FILESYSTEM_H
//----------------------------------------------------------------------------//
