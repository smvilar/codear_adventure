#ifndef HE_TRIGGERBEHAVIOR_H
#define HE_TRIGGERBEHAVIOR_H
//----------------------------------------------------------------------------//
#include <vector>
#include <string>
#include <boost/any.hpp>
//----------------------------------------------------------------------------//
#include "dllexport.h"
#include "gameobject/behavior.h"
//----------------------------------------------------------------------------//
namespace he {
//----------------------------------------------------------------------------//
class Attribute;
//----------------------------------------------------------------------------//
class ENGINE_API TriggerBehavior : public Behavior
{
public:
	TriggerBehavior() : active_(true) {}
	virtual Behavior* clone() const { return new TriggerBehavior; }

	virtual void handleMessage(const Message &message);

private:
	virtual void activate();

private:
	struct Condition
	{
		std::string name;
		bool met;

		Condition(const std::string &name) : name(name), met(false) {}
	};

	std::vector<Condition> conditions_;

private:
	struct Action
	{
		std::string name;
		std::vector<Attribute*> args;

		Action(const std::string &name, const std::vector<Attribute*> args)
			: name(name), args(args) {}
	};

	std::vector<Action> actions_;

private:
	bool active_;

	bool allConditionsMet() const;
	void doActions();
	void resetConditions();
};
//----------------------------------------------------------------------------//
} // end namespace he
//----------------------------------------------------------------------------//
#endif // HE_TRIGGERBEHAVIOR_H
