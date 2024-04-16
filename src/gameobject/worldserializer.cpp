#include "gameobject/worldserializer.h"
//----------------------------------------------------------------------------//
#include <algorithm>
#include <any>
#include <functional>
#include <string>
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

	for (GameObject* object : world.objects_)
	{
		if (!isIgnored(*object))
			root.append(serializeObject(*object, world));
	}

	Json::StyledStreamWriter writer;
	writer.write(os, root);
}
//----------------------------------------------------------------------------//
Json::Value WorldSerializer::serializeObject(const GameObject &object, const World &world)
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
Json::Value WorldSerializer::serializeAttributes(const GameObject &object)
{
	Json::Value attrs(Json::objectValue);
	const GameObject::AttributeMap &attributes = object.attributes_;

	for (const auto& attribute : attributes)
	{
		Json::Value attrValue = serializeAttributeValue(*attribute.second);
		if (attrValue.type() != Json::nullValue)
			attrs[attribute.first] = attrValue;
	}
	return attrs;
}
//----------------------------------------------------------------------------//
Json::Value WorldSerializer::serializeAttributeValue(const Attribute &attribute)
{
	std::any anyValue = attribute.value_;
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
Json::Value WorldSerializer::serializeBehaviors(const GameObject &object, const World &world)
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

	for (const auto& child : root)
	{
		GameObject *object = new GameObject("unnamed");
		deserializeObject(*object, child, world);
		world.addObject(object);
	}
}
//----------------------------------------------------------------------------//
void WorldSerializer::deserializeObject(GameObject &object, const Json::Value &jsObject, const World &world)
{
	object.name = jsObject["name"].asCString();
	deserializeAttributes(object, jsObject["attributes"]);
	deserializeBehaviors(object, jsObject["behaviors"], world);
}
//----------------------------------------------------------------------------//
void WorldSerializer::deserializeAttributes(GameObject &object, const Json::Value &jsAttrs)
{
	using std::cout; using std::cerr; using std::endl;

	const Json::Value::Members attrNames = jsAttrs.getMemberNames();
	for (const auto& attrName : attrNames)
	{
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
Attribute* WorldSerializer::deserializeAttributeValue(const Json::Value &jsValue)
{
	if (jsValue.isInt())
	{
		return new Attribute(jsValue.asInt());
	}
	else if (jsValue.isDouble())
	{
		return new Attribute(jsValue.asDouble());
	}
	else if (jsValue.isBool())
	{
		return new Attribute(jsValue.asBool());
	}
	else if (jsValue.isString())
	{
		return new Attribute(jsValue.asString());
	}
	else if (jsValue.isArray())
	{
		std::vector<Attribute*> vec(jsValue.size());
		std::transform(
			jsValue.begin(), jsValue.end(), vec.begin(),
			&WorldSerializer::deserializeAttributeValue
		);

		return new Attribute(vec);
	}
	else if (jsValue.isObject())
	{
		std::map<std::string, Attribute*> dict;
		const Json::Value::Members& memberNames = jsValue.getMemberNames();
		std::transform(
			memberNames.cbegin(), memberNames.cend(), std::inserter(dict, dict.end()),
			[&jsValue](const std::string& memberName) {
				return std::make_pair(memberName, WorldSerializer::deserializeAttributeValue(jsValue[memberName]));
			}
		);
		return new Attribute(dict);
	}

	return nullptr;
}
//----------------------------------------------------------------------------//
void WorldSerializer::deserializeBehaviors(GameObject &object, const Json::Value &jsBehavs, const World &world)
{
	using std::cerr;
	using std::endl;

	if (!jsBehavs.isArray())
	{
		cerr << "The behaviors are bad formatted" << endl;
		return;
	}

	for (const auto &behaviorName : jsBehavs)
	{
		Behavior* behavior = world.createBehavior(behaviorName.asCString());
		if (behavior)
		{
			object.addBehavior(behavior);
		}
		else
		{
			cerr << behaviorName << " not found" << endl;
		}
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
	return std::find(ignoredObjects_.begin(), ignoredObjects_.end(), object.name)
		!= ignoredObjects_.end();
}
//----------------------------------------------------------------------------//
void WorldSerializer::cleanWorld(World &world) const
{
	for (GameObject* object : world.objects_)
	{
		if (!isIgnored(*object))
		{
			world.removeObject(object);
		}
	}
}
//----------------------------------------------------------------------------//
