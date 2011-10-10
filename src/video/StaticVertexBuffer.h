#ifndef FORAGERS_STATICVERTEXBUFFER_H
#define FORAGERS_STATICVERTEXBUFFER_H
//----------------------------------------------------------------------------//
#include "DllExport.h"
#include "video/Vertex.h"
//----------------------------------------------------------------------------//
#define BUFFER_OFFSET(i) ((char*)NULL + (i))
//----------------------------------------------------------------------------//
namespace foragers
{
//----------------------------------------------------------------------------//
class ENGINE_API StaticVertexBuffer
{
public:
	StaticVertexBuffer();
	~StaticVertexBuffer();

	void init(Vertex2D* vertices, u32 vertexCount);
	void deinit();

	void render();

private:
	u32 _vboID;
	u32 _iboID;

	u32 _vertexCount;
	u32 _indexCount;
};
//----------------------------------------------------------------------------//
} // end namespace foragers
//----------------------------------------------------------------------------//
#endif // FORAGERS_STATICVERTEXBUFFER_H
