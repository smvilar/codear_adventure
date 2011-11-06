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
Screen* Screen::resolveTransition(const std::string &transition)
{
	TransitionMap::iterator it = transitions_.find(transition);
	if (it == transitions_.end())
	{
		std::cerr << "Error applying transition '" << transition << "' to screen " << name << std::endl;
		return 0;
	}
	return it->second;
}
//----------------------------------------------------------------------------//
