#include "screen/screendirector.h"
//----------------------------------------------------------------------------//
#include <fstream>
//----------------------------------------------------------------------------//
#include "json/json.h"
#include "screen/screen.h"
#include "gameobject/world.h"
//----------------------------------------------------------------------------//
using namespace he;
//----------------------------------------------------------------------------//
bool ScreenDirector::parse(const char *filename)
{
	using std::string;

	std::ifstream ifs(filename);
	Json::Reader reader;
	Json::Value root;
	reader.parse(ifs, root);

	for (size_t i = 0; i < root.size(); ++i)
	{
		Json::Value jsScreen = root[i];
		Screen *screen = new Screen;
		screen->name = jsScreen["name"].asString();
		screen->filename = jsScreen["filename"].asString();

		// add to map
		screens_[screen->name] = screen;
		std::cout << "Adding screen '" << screen->name << "'" << std::endl;
	}

	// now map the transitions
	for (size_t i = 0; i < root.size(); ++i)
	{
		Json::Value jsScreen = root[i];
		const string &screenName = jsScreen["name"].asString();
		Json::Value jsTransitions = jsScreen["transitions"];
		Json::Value::Members transNames = jsTransitions.getMemberNames();
		for (size_t j = 0; j < transNames.size(); ++j)
		{
			const string &transName = transNames[i];
			const string &toScreenName = jsTransitions[transName].asString();
			screens_[screenName]->addTransition(
						transNames[i].c_str(), screens_[toScreenName]);

			std::cout << screenName << " [ " << transName << " ]-> " << toScreenName << std::endl;
		}
	}
}
//----------------------------------------------------------------------------//
void ScreenDirector::show(const char *screenName, World &world)
{
	ScreenMap::iterator it = screens_.find(screenName);
	if (it == screens_.end())
	{
		std::cerr << "Error showing screen " << screenName << std::endl;
		return;
	}

	currentScreen_ = it->second;

	world.loadState(currentScreen_->filename.c_str());
}
//----------------------------------------------------------------------------//
void ScreenDirector::transition(const char *transitionName, World &world)
{
	currentScreen_ = currentScreen_->resolveTransition(transitionName);
	if (currentScreen_)
		world.loadState(currentScreen_->filename.c_str());
}
//----------------------------------------------------------------------------//
