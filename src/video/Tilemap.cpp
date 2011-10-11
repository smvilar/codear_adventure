#include "video/Tilemap.h"
//----------------------------------------------------------------------------//
#include <fstream>
#include <rapidxml.hpp>
//----------------------------------------------------------------------------//
#include "core/Assert.h"
//#include "util/base64.h"
#include "util/Util.h"
#include "video/Renderer.h"
#include "resource/ResourceManager.h"
//----------------------------------------------------------------------------//
using namespace he;
//----------------------------------------------------------------------------//
Tilemap::Tilemap()
{
}
//----------------------------------------------------------------------------//
Tilemap::~Tilemap()
{
}
//----------------------------------------------------------------------------//
void Tilemap::load(ResourceManager& resManager, const char *filename)
{
	using namespace rapidxml;
	using std::ifstream;
	using std::string;
	using std::vector;

	ifstream ifs(filename);

	// get length of file
	ifs.seekg(0, ifstream::end);
	u32 length = static_cast<u32>(ifs.tellg());
	ifs.seekg(0, ifstream::beg);

	// allocate memory
	char* buffer = new char[length+1];

	// read data as a block
	ifs.read(buffer, length);
	u32 gcount = static_cast<u32>(ifs.gcount());
	buffer[gcount] = '\0'; // terminate in zero!

	// parse xml
	xml_document<> doc;
	doc.parse<parse_trim_whitespace>(buffer);

	// everything in the tiled format is inside this map node
	xml_node<>* map = doc.first_node("map");
	Assert(strcmp(map->first_attribute("orientation")->value(), "orthogonal") == 0, "Tilemap orientation must be orthogonal!");
	_size.x = fromString<f32>(map->first_attribute("width")->value());
	_size.y = fromString<f32>(map->first_attribute("height")->value());
	
	// TODO: multiple tilesets
	Tileset tileset;
	xml_node<>* tilesetNode = map->first_node("tileset");
	tileset.tileWidth = fromString<u32>(tilesetNode->first_attribute("tilewidth")->value());
	tileset.tileHeight = fromString<u32>(tilesetNode->first_attribute("tileheight")->value());
	tileset.firstTileId = fromString<u32>(tilesetNode->first_attribute("firstgid")->value());
	char* textureFilename = tilesetNode->first_node("image")->first_attribute("source")->value();
	tileset.texture = resManager.get<Texture>(textureFilename);
	_tilesets.push_back(tileset);

	// TODO: multiple layers
	Layer layer;
	xml_node<>* layerNode = map->first_node("layer");
	layer.name = layerNode->first_attribute("name")->value();
	layer.width = fromString<u32>(layerNode->first_attribute("width")->value());
	layer.height = fromString<u32>(layerNode->first_attribute("height")->value());

	// Decrypt data!
	xml_node<>* dataNode = layerNode->first_node("data");
	//Assert(strcmp(dataNode->first_attribute("encoding")->value(), "base64") == 0, "Tilemap encoding must be base64!");
	//Assert(strcmp(dataNode->first_attribute("compression")->value(), "gzip") == 0, "Tilemap compression must be gzip!");
	Assert(strcmp(dataNode->first_attribute("encoding")->value(), "csv") == 0, "Tilemap encoding must be csv!");
	string data = dataNode->value();

	// reserve memory for tile vector!
	layer.tiles.reserve(layer.width * layer.height);
	string sub;
	size_t commaPos = 0;
	while (commaPos < data.size())
	{
		size_t nextCommaPos = data.find_first_of(',', commaPos);
		if (nextCommaPos == string::npos)
			nextCommaPos = data.size();
		sub = data.substr(commaPos, nextCommaPos - commaPos);
		Tile tile;
		tile.id = fromString<u32>(sub.c_str());
		layer.tiles.push_back(tile);

		commaPos = nextCommaPos+1;
	}
	Assert(layer.tiles.size() == layer.width * layer.height, "The number of tiles read doesn't match the size of the tilemap!");
	_layers.push_back(layer);

	// deallocate memory
	delete [] buffer;

	// init static vb
	prerender();
}
//----------------------------------------------------------------------------//
void Tilemap::update(u32 elapsedMs)
{
}
//----------------------------------------------------------------------------//
void Tilemap::render(Renderer& renderer)
{
	renderer.setTexture(_tilesets[0].texture);
	_staticVB.render();
}
//----------------------------------------------------------------------------//
void Tilemap::prerender()
{
	for (size_t layerIdx=0; layerIdx<_layers.size(); ++layerIdx)
	{
		Layer& layer = _layers[layerIdx];

		Vertex2D* vertices = new Vertex2D[layer.tiles.size()*4];
		u32 vertexCount = 0;
		
		for (size_t tileIdx=0; tileIdx<layer.tiles.size(); ++tileIdx)
		{
			Tile& tile = layer.tiles[tileIdx];
			//TODO: multiple tilesets
			Tileset& tileset = _tilesets[0];
			TexturePtr texture = tileset.texture;
			u32 tileWidth = tileset.tileWidth;
			u32 tileHeight = tileset.tileHeight;

			// compute position of the tile
			u32 x = (tileIdx % layer.width) * tileWidth;
			u32 y = (tileIdx / layer.width) * tileHeight;

			// compute uv
			u32 textureWidth = texture->getSize().x;
			u32 textureHeight = texture->getSize().y;

			u32 tileId = tile.id - tileset.firstTileId;
			u32 tilesPerWidth = textureWidth / tileWidth;
			f32 u1 = ((tileId % tilesPerWidth) * tileWidth) / (f32)textureWidth;
			f32 v1 = ((tileId / tilesPerWidth) * tileHeight) / (f32)textureHeight;
			f32 u2 = u1 + (tileWidth / (f32)textureWidth);
			f32 v2 = v1 + (tileHeight / (f32)textureHeight);

			vertices[vertexCount++] = Vertex2D((f32)x, (f32)y, u1, v1);
			vertices[vertexCount++] = Vertex2D((f32)x, (f32)(y+tileHeight), u1, v2);
			vertices[vertexCount++] = Vertex2D((f32)(x+tileWidth), (f32)(y+tileHeight), u2, v2);
			vertices[vertexCount++] = Vertex2D((f32)(x+tileWidth), (f32)y, u2, v1);
		}

		_staticVB.init(vertices, vertexCount);

		delete [] vertices;
	}
}
//----------------------------------------------------------------------------//
const Vector2f& Tilemap::getSize() const
{
	return _size;
}
//----------------------------------------------------------------------------//