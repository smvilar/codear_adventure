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
};
//----------------------------------------------------------------------------//
#endif // DATABASEBEHAVIOR_H
