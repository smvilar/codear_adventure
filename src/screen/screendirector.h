#ifndef HE_SCREENDIRECTOR_H
#define HE_SCREENDIRECTOR_H
//----------------------------------------------------------------------------//
#include <map>
//----------------------------------------------------------------------------//
#include "DllExport.h"
//----------------------------------------------------------------------------//
namespace he {
//----------------------------------------------------------------------------//
class Screen;
class World;
//----------------------------------------------------------------------------//
class ENGINE_API ScreenDirector
{
public:
	bool parse(const char *filename);

	void show(const char *screenName, World &world);
	void transition(const char *transitionName, World &world);

private:
	typedef std::map<std::string, Screen*> ScreenMap;
	ScreenMap screens_;

	Screen* currentScreen_;
};
//----------------------------------------------------------------------------//
} // end namespace he
//----------------------------------------------------------------------------//
#endif // HE_SCREENDIRECTOR_H
