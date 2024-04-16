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
	void deserialize(World &world, const std::string &text) const;

	void addIgnoredObject(const std::string &name);

private:
	static Json::Value serializeObject(const GameObject &object, const World &world);
	static Json::Value serializeAttributes(const GameObject &object);
	static Json::Value serializeBehaviors(const GameObject &object, const World &world);
	static Json::Value serializeAttributeValue(const Attribute &attribute);

private:
	static void deserializeObject(GameObject& object, const Json::Value &jsObject, const World &world);
	static void deserializeAttributes(GameObject& object, const Json::Value &jsAttrs);
	static void deserializeBehaviors(GameObject& object, const Json::Value &jsBehavs, const World &world);
	static Attribute* deserializeAttributeValue(const Json::Value& jsValue);

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
