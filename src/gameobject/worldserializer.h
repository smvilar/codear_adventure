#ifndef HE_WORLDSERIALIZER_H
#define HE_WORLDSERIALIZER_H
//----------------------------------------------------------------------------//
#include <iosfwd>
#include <list>
//----------------------------------------------------------------------------//
#include "DllExport.h"
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
	void deserialize(World &world, std::istream &is) const;

	void addIgnoredObject(const char *name);

private:
	Json::Value serializeObject(const GameObject &object, const World &world) const;
	Json::Value serializeAttributes(const GameObject &object) const;
	Json::Value serializeBehaviors(const GameObject &object, const World &world) const;
	Json::Value serializeAttributeValue(const Attribute &attribute) const;

private:
	void deserializeObject(GameObject& object, const Json::Value &jsObject, const World &world) const;
	void deserializeAttributes(GameObject& object, const Json::Value &jsAttrs) const;
	void deserializeBehaviors(GameObject& object, const Json::Value &jsBehavs, const World &world) const;
	Attribute* deserializeAttributeValue(const Json::Value &jsValue) const;

private:
	typedef std::list<std::string> StringList;
	StringList _ignoredObjects;
};
//----------------------------------------------------------------------------//
} // end namespace he
//----------------------------------------------------------------------------//
#endif // HE_WORLDSERIALIZER_H
