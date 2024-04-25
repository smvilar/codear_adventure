#include "gameobject/worldserializer.h"
//----------------------------------------------------------------------------//
#include <algorithm>
#include <any>
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
void WorldSerializer::parse(World &world, const std::string &text) const
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
		parseObject(*object, child, world);
		world.addObject(object);
	}
}
//----------------------------------------------------------------------------//
void WorldSerializer::parseObject(GameObject &object, const Json::Value &json, const World &world)
{
	if (!json["name"].isNull())
		object.name = json["name"].asCString();
	parseAttributes(object, json["attributes"]);
	parseBehaviors(object, json["behaviors"], world);
}
//----------------------------------------------------------------------------//
void WorldSerializer::parseAttributes(GameObject &object, const Json::Value &jsonAttrs)
{
	using std::cout; using std::cerr; using std::endl;

	if (!jsonAttrs.isObject())
	{
		cerr << "The attributes are bad formatted" << endl;
		return;
	}

	const Json::Value::Members& attrNames = jsonAttrs.getMemberNames();
	for (const auto& attrName : attrNames)
	{
		Json::Value value = jsonAttrs[attrName];

		Attribute *attribute = parseAttributeValue(value);

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
Attribute* WorldSerializer::parseAttributeValue(const Json::Value &jsonValue)
{
	if (jsonValue.isInt())
	{
		return new Attribute(jsonValue.asInt());
	}
	else if (jsonValue.isDouble())
	{
		return new Attribute(jsonValue.asDouble());
	}
	else if (jsonValue.isBool())
	{
		return new Attribute(jsonValue.asBool());
	}
	else if (jsonValue.isString())
	{
		return new Attribute(jsonValue.asString());
	}
	else if (jsonValue.isArray())
	{
		std::vector<Attribute*> vec(jsonValue.size());
		std::transform(
			jsonValue.begin(), jsonValue.end(), vec.begin(),
			&WorldSerializer::parseAttributeValue
		);

		return new Attribute(vec);
	}
	else if (jsonValue.isObject())
	{
		std::map<std::string, Attribute*> dict;
		const Json::Value::Members& memberNames = jsonValue.getMemberNames();
		std::transform(
			memberNames.cbegin(), memberNames.cend(), std::inserter(dict, dict.end()),
			[&jsonValue](const std::string& memberName) {
				return std::make_pair(memberName, WorldSerializer::parseAttributeValue(jsonValue[memberName]));
			}
		);
		return new Attribute(dict);
	}

	return nullptr;
}
//----------------------------------------------------------------------------//
void WorldSerializer::parseBehaviors(GameObject &object, const Json::Value &jsonBehavs, const World &world)
{
	using std::cerr;
	using std::endl;

	if (!jsonBehavs.isArray())
	{
		cerr << "The behaviors are bad formatted" << endl;
		return;
	}

	for (const auto &behaviorName : jsonBehavs)
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
