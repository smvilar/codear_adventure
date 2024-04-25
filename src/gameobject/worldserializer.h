#ifndef HE_WORLDSERIALIZER_H
#define HE_WORLDSERIALIZER_H
//----------------------------------------------------------------------------//
#include <iosfwd>
#include <list>
//----------------------------------------------------------------------------//
#include "dllexport.h"
#include "json/json.h"
//----------------------------------------------------------------------------//
namespace he {
//----------------------------------------------------------------------------//
class World;
class GameObject;
class Attribute;
//----------------------------------------------------------------------------//
class ENGINE_API WorldSerializer
{
public:
	void serialize(const World &world, std::ostream &os) const;
	void parse(World &world, const std::string &text) const;

	void addIgnoredObject(const std::string &name);

	static Json::Value serializeObject(const GameObject &object, const World &world);
	static Json::Value serializeAttributes(const GameObject &object);
	static Json::Value serializeBehaviors(const GameObject &object, const World &world);
	static Json::Value serializeAttributeValue(const Attribute &attribute);

	static void parseObject(GameObject& object, const Json::Value &json, const World &world);
	static void parseAttributes(GameObject& object, const Json::Value &jsonAttrs);
	static void parseBehaviors(GameObject& object, const Json::Value &jsonBehavs, const World &world);
	static Attribute* parseAttributeValue(const Json::Value& jsonValue);

private:
	bool isIgnored(const GameObject &object) const;
	void cleanWorld(World &world) const;

private:
	typedef std::list<std::string> StringList;
	StringList ignoredObjects_;
};
//----------------------------------------------------------------------------//
} // end namespace he
//----------------------------------------------------------------------------//
#endif // HE_WORLDSERIALIZER_H
