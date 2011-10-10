#include "core/GameConfig.h"
//----------------------------------------------------------------------------//
#include <fstream>
#include <rapidxml_print.hpp>
//----------------------------------------------------------------------------//
#include "core/Assert.h"
#include "util/Util.h"
//----------------------------------------------------------------------------//
using namespace foragers;
//----------------------------------------------------------------------------//
GameConfig::GameConfig()
: name("Game")
, screenWidth(640)
, screenHeight(480)
, screenBpp(0)
, fullscreen(false)
, maxFramerate(0)
{
	// ...
}
//----------------------------------------------------------------------------//
GameConfig::~GameConfig()
{
}
//----------------------------------------------------------------------------//
bool GameConfig::load(const char* filename)
{
	using namespace rapidxml;
	using std::ifstream;

	ifstream ifs(filename);

	// get length of file
	ifs.seekg (0, ifstream::end);
	u32 length = static_cast<u32>(ifs.tellg());
	ifs.seekg (0, ifstream::beg);

	// allocate memory
	char* buffer = new char[length+1];

	// read data as a block
	ifs.read(buffer, length);
	std::streamsize gcount = ifs.gcount();
	buffer[gcount] = 0;

	// parse xml
	xml_document<> doc;
	doc.parse<0>(buffer);

	xml_node<> * root = doc.first_node("GameConfig");
	Assert(root, "Error parsing GameConfig");
	name = root->first_node("name")->value();
	getValueFromNode(root->first_node("screenWidth"), screenWidth);
	getValueFromNode(root->first_node("screenHeight"), screenHeight);
	getValueFromNode(root->first_node("screenBpp"), screenBpp);
	getValueFromNode(root->first_node("fullscreen"), fullscreen);
	getValueFromNode(root->first_node("maxFramerate"), maxFramerate);

	// deallocate memory
	delete [] buffer;

	return true;
}
//----------------------------------------------------------------------------//
bool GameConfig::save(const char* filename)
{
	using namespace rapidxml;
	using std::ofstream;

	xml_document<> doc;

	xml_node<> * root = doc.allocate_node(node_element, "GameConfig");

	xml_node<> * nameNode = createNode(doc, "name", name);
	xml_node<> * screenWidthNode = createNode(doc, "screenWidth", screenWidth);
	xml_node<> * screenHeightNode = createNode(doc, "screenHeight", screenHeight);
	xml_node<> * screenBppNode = createNode(doc, "screenBpp", screenBpp);
	xml_node<> * fullscreenNode = createNode(doc, "fullscreen", fullscreen);
	xml_node<> * maxFramerateNode = createNode(doc, "maxFramerate", maxFramerate);

	root->append_node(nameNode);
	root->append_node(screenWidthNode);
	root->append_node(screenHeightNode);
	root->append_node(screenBppNode);
	root->append_node(fullscreenNode);
	root->append_node(maxFramerateNode);

	doc.append_node(root);

	ofstream ofs(filename);
	ofs << doc;

	// TODO: check for errors...
	return true;
}
//----------------------------------------------------------------------------//
