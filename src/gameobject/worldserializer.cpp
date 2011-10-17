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
	Json::Value root(Json::objectValue);
	Json::Value jsObjects(Json::arrayValue);

	const World::ObjectVector& objects = world._objects;

	for (size_t i = 0; i < objects.size(); ++i)
	{
		const GameObject& object = *objects[i];
		StringList::const_iterator it = std::find(
					_ignoredObjects.begin(),
					_ignoredObjects.end(),
					object.name);
		// only serialize if it's not in the ignoredList
		if (it == _ignoredObjects.end())
		{
			jsObjects.append(serializeObject(object, world));
		}
	}
	root["objects"] = jsObjects;

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
	const GameObject::AttributeMap &attributes = object._attributes;
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
		return Json::Value(attribute.getValue<int>());
	else if (anyValue.type() == typeid(float))
		return Json::Value(attribute.getValue<float>());
	else if (anyValue.type() == typeid(bool))
		return Json::Value(attribute.getValue<bool>());
	else if (anyValue.type() == typeid(std::string))
		return Json::Value(attribute.getValue<std::string>());
	// TODO: array!
	return Json::Value();
}
//----------------------------------------------------------------------------//
Json::Value WorldSerializer::serializeBehaviors(const GameObject &object, const World &world) const
{
	Json::Value behavs(Json::arrayValue);

	const World::BehaviorMap &registeredBehaviors = world._behaviors;
	const GameObject::BehaviorVector &behaviors = object._behaviors;

	// We have to seach the registeredBehaviors map to find the names
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
void WorldSerializer::deserialize(World &world, std::istream &is) const
{
	Json::Value root;
	Json::Reader reader;

	bool parsed = reader.parse(is, root, false);
	if (!parsed)
	{
		std::cerr << reader.getFormatedErrorMessages() << std::endl;
		return;
	}

	Json::Value objs = root["objects"];
	for (size_t i = 0; i < objs.size(); ++i)
	{
		GameObject *object = new GameObject("unnamed");
		deserializeObject(*object, objs[i], world);
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
			cout << "Adding attribute " << attrName << endl;
			object.addAttribute(attrName.c_str(), attribute);
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
		// recurse
		for (size_t i = 0; i < jsValue.size(); ++i)
			vec.push_back(deserializeAttributeValue(jsValue[i]));
		attribute = new Attribute(vec);
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
void WorldSerializer::addIgnoredObject(const char *name)
{
	_ignoredObjects.push_back(name);
}
//----------------------------------------------------------------------------//
