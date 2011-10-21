#include "screen/screen.h"
//----------------------------------------------------------------------------//
#include <iostream>
//----------------------------------------------------------------------------//
using namespace he;
//----------------------------------------------------------------------------//
void Screen::addTransition(const char *name, Screen *screen)
{
	transitions_[name] = screen;
}
//----------------------------------------------------------------------------//
Screen* Screen::resolveTransition(const char *name)
{
	TransitionMap::iterator it = transitions_.find(name);
	if (it == transitions_.end())
	{
		std::cerr << "Error applying transition '" << name << "' to screen " << name << std::endl;
		return 0;
	}
	return it->second;
}
//----------------------------------------------------------------------------//
