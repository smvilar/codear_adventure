#include "gameobject/worldserializer.h"
//----------------------------------------------------------------------------//
#include <string>
#include <algorithm>
//----------------------------------------------------------------------------//
#include "json/json.h"
#include "gameobject/world.h"
#include "gameobject/gameobject.h"
#include "gameobject/behavior.h"
//----------------------------------------------------------------------------//
using namespace he;
//----------------------------------------------------------------------------//
void WorldSerializer::serialize(const World &world, std::ostream &os) const
{
	Json::Value root(Json::arrayValue);

	const World::ObjectVector& objects = world.objects_;

	for (size_t i = 0; i < objects.size(); ++i)
	{
		const GameObject &object = *objects[i];
		if (!isIgnored(object))
			root.append(serializeObject(object, world));
	}

	Json::StyledStreamWriter writer;
	writer.write(os, root);
}
//----------------------------------------------------------------------------//
Json::Value WorldSerializer::serializeObject(const GameObject &object, const World &world) const
{
	Json::Value objRoot(Json::objectValue);
	Json::Value attributes = serializeAttributes(object);
	Json::Value behaviors = serializeBehaviors(object, world);

	objRoot["name"] = object.name;
	objRoot["attributes"] = attributes;
	objRoot["behaviors"] = behaviors;

	return objRoot;
}
//----------------------------------------------------------------------------//
Json::Value WorldSerializer::serializeAttributes(const GameObject &object) const
{
	Json::Value attrs(Json::objectValue);
	const GameObject::AttributeMap &attributes = object.attributes_;
	GameObject::AttributeMap::const_iterator it = attributes.begin();
	for (; it != attributes.end(); ++it)
	{
		Json::Value attrValue = serializeAttributeValue(*it->second);
		if (attrValue.type() != Json::nullValue)
			attrs[it->first] = attrValue;
	}
	return attrs;
}
//----------------------------------------------------------------------------//
Json::Value WorldSerializer::serializeAttributeValue(const Attribute &attribute) const
{
	boost::any anyValue = attribute._value;
	if (anyValue.type() == typeid(int))
		return Json::Value(attribute.get<int>());
	else if (anyValue.type() == typeid(float))
		return Json::Value(attribute.get<float>());
	else if (anyValue.type() == typeid(bool))
		return Json::Value(attribute.get<bool>());
	else if (anyValue.type() == typeid(std::string))
		return Json::Value(attribute.get<std::string>());
	// TODO: arrays, objects
	return Json::Value();
}
//----------------------------------------------------------------------------//
Json::Value WorldSerializer::serializeBehaviors(const GameObject &object, const World &world) const
{
	Json::Value behavs(Json::arrayValue);

	const World::BehaviorMap &registeredBehaviors = world.behaviors_;
	const GameObject::BehaviorVector &behaviors = object.behaviors_;

	// We have to search the registeredBehaviors map to find the names
	// of the used behaviors in the object
	GameObject::BehaviorVector::const_iterator it = behaviors.begin();
	for (; it != behaviors.end(); ++it)
	{
		Behavior *behavior = *it;

		World::BehaviorMap::const_iterator itMap = registeredBehaviors.begin();
		for (; itMap != registeredBehaviors.end(); ++itMap)
		{
			Behavior *registeredBehavior = itMap->second;
			if (typeid(*behavior) == typeid(*registeredBehavior))
			{
				behavs.append(itMap->first);
			}
		}
	}

	return behavs;
}
//----------------------------------------------------------------------------//
void WorldSerializer::deserialize(World &world, const std::string &text) const
{
	Json::Value root;
	Json::Reader reader;

	bool parsed = reader.parse(text, root, false);
	if (!parsed)
	{
		std::cerr << reader.getFormatedErrorMessages() << std::endl;
		return;
	}

	cleanWorld(world);

	for (size_t i = 0; i < root.size(); ++i)
	{
		GameObject *object = new GameObject("unnamed");
		deserializeObject(*object, root[i], world);
		world.addObject(object);
	}
}
//----------------------------------------------------------------------------//
void WorldSerializer::deserializeObject(GameObject &object, const Json::Value &jsObject, const World &world) const
{
	object.name = jsObject["name"].asCString();
	deserializeAttributes(object, jsObject["attributes"]);
	deserializeBehaviors(object, jsObject["behaviors"], world);
}
//----------------------------------------------------------------------------//
void WorldSerializer::deserializeAttributes(GameObject &object, const Json::Value &jsAttrs) const
{
	using std::cout; using std::cerr; using std::endl;

	const Json::Value::Members attrNames = jsAttrs.getMemberNames();
	Json::Value::Members::const_iterator it = attrNames.begin();
	for (; it != attrNames.end(); ++it)
	{
		const std::string& attrName = *it;
		Json::Value value = jsAttrs[attrName];

		Attribute *attribute = deserializeAttributeValue(value);

		if (attribute)
		{
			//cout << "Adding attribute " << attrName << endl;
			object.addAttribute(attrName, attribute);
		}
		else
		{
			cerr << "The type of attribute '" << attrName
				 << "' isn't supported" << endl;
		}
	}
}
//----------------------------------------------------------------------------//
Attribute* WorldSerializer::deserializeAttributeValue(const Json::Value &jsValue) const
{
	Attribute* attribute = 0;

	if (jsValue.isInt())
	{
		attribute = new Attribute(jsValue.asInt());
	}
	else if (jsValue.isDouble())
	{
		attribute = new Attribute(jsValue.asDouble());
	}
	else if (jsValue.isBool())
	{
		attribute = new Attribute(jsValue.asBool());
	}
	else if (jsValue.isString())
	{
		attribute = new Attribute(jsValue.asString());
	}
	else if (jsValue.isArray())
	{
		std::vector<Attribute*> vec;
		vec.reserve(jsValue.size());
		for (size_t i = 0; i < jsValue.size(); ++i)
		{
			//recurse
			vec.push_back(deserializeAttributeValue(jsValue[i]));
		}
		attribute = new Attribute(vec);
	}
	else if (jsValue.isObject())
	{
		std::map<std::string, Attribute*> dict;
		Json::Value::Members memberNames = jsValue.getMemberNames();
		for (size_t i = 0; i < jsValue.size(); ++i)
		{
			//recurse
			const std::string &memberName = memberNames[i];
			dict[memberName] = deserializeAttributeValue(jsValue[memberName]);
		}
		attribute = new Attribute(dict);
	}

	return attribute;
}
//----------------------------------------------------------------------------//
void WorldSerializer::deserializeBehaviors(GameObject &object, const Json::Value &jsBehavs, const World &world) const
{
	using std::cerr;
	using std::endl;

	if (!jsBehavs.isArray())
	{
		cerr << "The behaviors are bad formatted" << endl;
		return;
	}

	for (size_t i = 0; i < jsBehavs.size(); ++i)
	{
		const char* behaviorName = jsBehavs[i].asCString();

		Behavior* behavior = world.createBehavior(behaviorName);
		if (behavior)
		{
			object.addBehavior(behavior);
		}
		else
			cerr << behaviorName << " not found" << endl;
	}
}
//----------------------------------------------------------------------------//
void WorldSerializer::addIgnoredObject(const std::string &name)
{
	ignoredObjects_.push_back(name);
}
//----------------------------------------------------------------------------//
bool WorldSerializer::isIgnored(const GameObject &object) const
{
	StringList::const_iterator it =
		std::find(ignoredObjects_.begin(), ignoredObjects_.end(), object.name);
	return it != ignoredObjects_.end();
}
//----------------------------------------------------------------------------//
void WorldSerializer::cleanWorld(World &world) const
{
	for (size_t i = 0; i < world.objects_.size(); ++i)
	{
		GameObject &object = *world.objects_[i];
		if (!isIgnored(object))
		{
			world.removeObject(&object);
		}
	}
}
//----------------------------------------------------------------------------//
