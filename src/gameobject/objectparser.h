#ifndef HE_OBJECTPARSER_H
#define HE_OBJECTPARSER_H
//----------------------------------------------------------------------------//
// This is a "inner" header file, it won't be visible to the library user
//----------------------------------------------------------------------------//
#include "gameobject/world.h"
#include "json/json.h"
//----------------------------------------------------------------------------//
namespace he
{
//----------------------------------------------------------------------------//
class GameObject;
class Attribute;
//----------------------------------------------------------------------------//
class ObjectParser
{
public:
	bool parse(const char* filename, GameObject& object, const World *world = 0);

private:
	void parseAttributes(const Json::Value& jsonValue, GameObject& object);
	void parseBehaviors(const Json::Value& jsonValue, GameObject& object,
						const World &world);

	Attribute* resolveType(const Json::Value& jsonValue);
};
//----------------------------------------------------------------------------//
} // end namespace he
//----------------------------------------------------------------------------//
#endif // HE_OBJECTPARSER_H
