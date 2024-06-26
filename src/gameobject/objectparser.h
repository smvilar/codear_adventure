#ifndef HE_OBJECTPARSER_H
#define HE_OBJECTPARSER_H
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
	bool parse(const std::string &document, GameObject &object, const World *world = nullptr) const;

private:
	void parseAttributes(const Json::Value &jsonValue, GameObject &object) const;
	void parseBehaviors(const Json::Value &jsonValue, GameObject &object, const World &world) const;

	Attribute* resolveType(const Json::Value& jsonValue) const;
};
//----------------------------------------------------------------------------//
} // end namespace he
//----------------------------------------------------------------------------//
#endif // HE_OBJECTPARSER_H
