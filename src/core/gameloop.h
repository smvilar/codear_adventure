#ifndef FORAGERS_GAMELOOP_H
#define FORAGERS_GAMELOOP_H
//----------------------------------------------------------------------------//
#include "DllExport.h"
//----------------------------------------------------------------------------//
namespace foragers {
//----------------------------------------------------------------------------//
class ENGINE_API GameLoop
{
public:
	void start(const char *gameFilename) const;
};
//----------------------------------------------------------------------------//
} // end namespace foragers
//----------------------------------------------------------------------------//
#endif // FORAGERS_GAMELOOP_H
