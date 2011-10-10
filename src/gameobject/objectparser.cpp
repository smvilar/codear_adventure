#include "objectparser.h"
//----------------------------------------------------------------------------//
#include <fstream>
//----------------------------------------------------------------------------//
#include "json/json.h"
#include "gameobject/gameobject.h"
#include "gameobject/goattribute.h"
#include "gameobject/gobehavior.h"
//----------------------------------------------------------------------------//
using namespace foragers;
//----------------------------------------------------------------------------//
bool ObjectParser::parse(const char *filename, GameObject &object,
						 const GOWorld &world)
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
	parseBehaviors(root["behaviors"], object, world);

	return true;
}
//----------------------------------------------------------------------------//
void ObjectParser::parseAttributes(const Json::Value &attrsValue,
								   GameObject &object)
{
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
		GOAttribute *attribute = 0;

		if (value.isInt())
			attribute = new GOAttribute(value.asInt());
		else if (value.isBool())
			attribute = new GOAttribute(value.asBool());
		else if (value.isString())
			attribute = new GOAttribute(value.asString());
		else
			cerr << "The type of attribute" << attrName
				 << "isn't supported" << endl;

		if (attribute)
		{
			std::cout << "Adding attribute " << attrName << endl;
			object.addAttribute(attrName.c_str(), attribute);
		}
	}
}
//----------------------------------------------------------------------------//
void ObjectParser::parseBehaviors(const Json::Value &behaviorsValue,
								  GameObject &object, const GOWorld &world)
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

		GOBehavior* behavior = world.createBehavior(behaviorName);
		if (behavior)
		{
			object.addBehavior(behavior);
		}
		else
			cerr << behaviorName << " not found" << endl;
	}
}
//----------------------------------------------------------------------------//
