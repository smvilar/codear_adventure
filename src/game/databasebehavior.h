#ifndef DATABASEBEHAVIOR_H
#define DATABASEBEHAVIOR_H
//----------------------------------------------------------------------------//
#include <hierophantengine.h>
//----------------------------------------------------------------------------//
using namespace he;
//----------------------------------------------------------------------------//
class DatabaseBehavior : public Behavior
{
public:
	Behavior* clone() const { return new DatabaseBehavior; }

	void handleMessage(const Message &message);

private:
	void activate();

private:
	GameObject *databaseInput_;
	bool displayingResult_;

private:
	void searchDatabase(const std::string &text);
	void updateText(const std::string &text);
};
//----------------------------------------------------------------------------//
#endif // DATABASEBEHAVIOR_H
