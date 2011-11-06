#ifndef HE_SCREEN_H
#define HE_SCREEN_H
//----------------------------------------------------------------------------//
#include <string>
#include <map>
//----------------------------------------------------------------------------//
#include "dllexport.h"
//----------------------------------------------------------------------------//
namespace he {
//----------------------------------------------------------------------------//
// A screen is a set of objects to be displayed in a certain state of the game
//----------------------------------------------------------------------------//
class ENGINE_API Screen
{
public:
	std::string name;
	std::string filename;

public:
	void addTransition(const std::string &name, Screen *screen);
	Screen* resolveTransition(const std::string &name);

private:
	typedef std::map<std::string, Screen*> TransitionMap;
	TransitionMap transitions_;
};
//----------------------------------------------------------------------------//
} // end namespace he
//----------------------------------------------------------------------------//
#endif // HE_SCREEN_H
