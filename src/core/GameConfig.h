#ifndef FORAGERS_GAMECONFIG_H
#define FORAGERS_GAMECONFIG_H
//----------------------------------------------------------------------------//
#include <string>
#include "DllExport.h"
#include "util/IStoreable.h"
//----------------------------------------------------------------------------//
namespace foragers
{
//----------------------------------------------------------------------------//
// Stores the game initial configuration, implements IStoreable to load / save
// from a file
//----------------------------------------------------------------------------//
class ENGINE_API GameConfig
	: public IStoreable
{
public:
	GameConfig();
	~GameConfig();

	std::string		name;
	u32				screenWidth;
	u32				screenHeight;
	u32				screenBpp;
	bool				fullscreen;

	u32				maxFramerate;

/// IStoreable implementation
public:
	virtual bool	load(const char* filename);
	virtual bool	save(const char* filename);
};
//----------------------------------------------------------------------------//
} // end namespace foragers
//----------------------------------------------------------------------------//
#endif // FORAGERS_GAMECONFIG_H
