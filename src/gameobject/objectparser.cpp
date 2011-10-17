#include "objectparser.h"
//----------------------------------------------------------------------------//
#include <fstream>
//----------------------------------------------------------------------------//
#include "json/json.h"
#include "gameobject/gameobject.h"
#include "gameobject/attribute.h"
#include "gameobject/behavior.h"
//----------------------------------------------------------------------------//
using namespace he;
//----------------------------------------------------------------------------//
bool ObjectParser::parse(const char *filename, GameObject &object, const World *world) const
{
	std::ifstream ifs(filename);

	Json::Reader reader;
	Json::Value root;
	bool parsed = reader.parse(ifs, root);
	if (!parsed)
	{
		std::cerr << reader.getFormatedErrorMessages() << std::endl;
		return false;
	}

	object.name = root["name"].asCString();

	parseAttributes(root["attributes"], object);

	if (world)
		parseBehaviors(root["behaviors"], object, *world);

	return true;
}
//----------------------------------------------------------------------------//
void ObjectParser::parseAttributes(const Json::Value &attrsValue, GameObject &object) const
{
	using std::cout;
	using std::cerr;
	using std::endl;

	if (!attrsValue.isObject())
	{
		cerr << "The attributes are bad formatted" << endl;
		return;
	}

	const Json::Value::Members attrNames = attrsValue.getMemberNames();
	Json::Value::Members::const_iterator it = attrNames.begin();
	for (; it != attrNames.end(); ++it)
	{
		const std::string& attrName = *it;
		Json::Value value = attrsValue[attrName];

		Attribute *attribute = resolveType(value);

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
void ObjectParser::parseBehaviors(const Json::Value &behaviorsValue, GameObject &object, const World &world) const
{
	using std::cerr;
	using std::endl;

	if (!behaviorsValue.isArray())
	{
		cerr << "The behaviors are bad formatted" << endl;
		return;
	}

	for (size_t i = 0; i < behaviorsValue.size(); ++i)
	{
		const char* behaviorName = behaviorsValue[i].asCString();

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
Attribute* ObjectParser::resolveType(const Json::Value &jsonValue) const
{
	Attribute* attribute = 0;

	if (jsonValue.isInt())
	{
		attribute = new Attribute(jsonValue.asInt());
	}
	else if (jsonValue.isBool())
	{
		attribute = new Attribute(jsonValue.asBool());
	}
	else if (jsonValue.isString())
	{
		attribute = new Attribute(jsonValue.asString());
	}
	else if (jsonValue.isArray())
	{
		std::vector<Attribute*> vec;
		vec.reserve(jsonValue.size());
		// recurse
		for (size_t i = 0; i < jsonValue.size(); ++i)
			vec.push_back(resolveType(jsonValue[i]));
		attribute = new Attribute(vec);
	}

	return attribute;
}
//----------------------------------------------------------------------------//
