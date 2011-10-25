#ifndef HE_TRIGGERBEHAVIOR_H
#define HE_TRIGGERBEHAVIOR_H
//----------------------------------------------------------------------------//
#include <vector>
#include <string>
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
	std::vector<std::string> actions_;

private:
	bool allConditionsMet() const;
	void doActions();
};
//----------------------------------------------------------------------------//
} // end namespace he
//----------------------------------------------------------------------------//
#endif // HE_TRIGGERBEHAVIOR_H