#ifndef HE_DYNAMICVERTEXBUFFER_H
#define HE_DYNAMICVERTEXBUFFER_H
//----------------------------------------------------------------------------//
#include "DllExport.h"
#include "core/Types.h"
#include "video/Vertex.h"
//----------------------------------------------------------------------------//
#define BUFFER_OFFSET(i) ((char*)NULL + (i))
//----------------------------------------------------------------------------//
#include <map>
#include <vector>
//----------------------------------------------------------------------------//
namespace he
{
//----------------------------------------------------------------------------//
class ENGINE_API DynamicVertexBuffer
{
public:
	static const int MAX_VERTEX_MEMORY = 1024*1024; // 1MB reserved for vertex buffer
	static const int MAX_INDEX_MEMORY = ((MAX_VERTEX_MEMORY/(sizeof(Vertex2D) * 4)) * 6);
	static const int MAX_TEXTURES = 64;
	static const int MAX_TEXTURE_INDEXES = MAX_INDEX_MEMORY / MAX_TEXTURES;

	DynamicVertexBuffer();
	~DynamicVertexBuffer();

	void init();
	void deinit();

	void addVertex(f32 x, f32 y, f32 u, f32 v);

	void setCurrTexture(u32 textureID);

	void render();

private:
	u32 _vboID;
	u32 _iboID;

	Vertex2D* _vertexBuffer;
	u32	_vertexBufferSize;

	// All indexes for each texture. 
	// The first short of each array is the texture id and the next ones are the indexes.
	u16** _textureIndexBatch;

	// Amount of indexes for each texture
	u32* _indexSize;

	// Amount of textures
	u32 _textureBatchSize;

	u32 _currentTexture;
};
//----------------------------------------------------------------------------//
} // end namespace he
//----------------------------------------------------------------------------//
#endif