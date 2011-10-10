#ifndef FORAGERS_OBJECTPARSER_H
#define FORAGERS_OBJECTPARSER_H
//----------------------------------------------------------------------------//
// This is a "inner" header file, it won't be visible to the library user
//----------------------------------------------------------------------------//
#include "gameobject/goworld.h"
#include "json/json.h"
//----------------------------------------------------------------------------//
namespace foragers
{
//----------------------------------------------------------------------------//
class GameObject;
//----------------------------------------------------------------------------//
class ObjectParser
{
public:
	bool parse(const char* filename, GameObject& object, const GOWorld &world);

private:
	void parseAttributes(const Json::Value& jsonValue, GameObject& object);
	void parseBehaviors(const Json::Value& jsonValue, GameObject& object,
						const GOWorld &world);
};
//----------------------------------------------------------------------------//
} // end namespace foragers
//----------------------------------------------------------------------------//
#endif // FORAGERS_OBJECTPARSER_H
