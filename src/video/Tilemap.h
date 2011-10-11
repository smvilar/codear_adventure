#ifndef HE_TILEMAP_H
#define HE_TILEMAP_H
//----------------------------------------------------------------------------//
#include <vector>
//----------------------------------------------------------------------------//
#include "DllExport.h"
#include "core/Entity.h"
#include "video/Texture.h"
#include "math/Vector2.h"
#include "video/StaticVertexBuffer.h"
//----------------------------------------------------------------------------//
namespace he
{
//----------------------------------------------------------------------------//
class Renderer;
class ResourceManager;
//----------------------------------------------------------------------------//
class ENGINE_API Tilemap
	: public Entity
{
public:
	Tilemap();
	virtual ~Tilemap();

	void load(ResourceManager& resManager, const char* filename);

	virtual void update(u32 elapsedMs);
	virtual void render(Renderer& renderer);
	
	virtual const Vector2f& getSize() const;

private:    
	
	struct Tile
	{
		u32 id;
	};
	typedef std::vector<Tile>		TileVector;

	struct Tileset
	{
		TexturePtr texture;
		u32 tileWidth;
		u32 tileHeight;
		u32 firstTileId;
	};
	typedef std::vector<Tileset>	TilesetVector;

	struct Layer
	{
		TileVector tiles;
		std::string name;
		u32 width;
		u32 height;
		f32 opacity;
	};
	typedef std::vector<Layer>		LayerVector;

	TilesetVector _tilesets;
	LayerVector _layers;
	Vector2f _size;

/// Rendering
	StaticVertexBuffer _staticVB;

	void prerender();
};
//----------------------------------------------------------------------------//
} // end namespace he
//----------------------------------------------------------------------------//
#endif // HE_TILEMAP_H