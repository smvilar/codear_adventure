#include "screen/screen.h"
//----------------------------------------------------------------------------//
#include <iostream>
//----------------------------------------------------------------------------//
using namespace he;
//----------------------------------------------------------------------------//
void Screen::addTransition(const std::string &name, Screen *screen)
{
	transitions_[name] = screen;
}
//----------------------------------------------------------------------------//
Screen* Screen::resolveTransition(const std::string &name)
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
