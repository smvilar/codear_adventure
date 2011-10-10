#include "video/StaticVertexBuffer.h"
#include "core/Assert.h"
#include "video/glee.h"
//----------------------------------------------------------------------------//
using namespace foragers;
//----------------------------------------------------------------------------//
StaticVertexBuffer::StaticVertexBuffer()
{
}
//----------------------------------------------------------------------------//
StaticVertexBuffer::~StaticVertexBuffer()
{
}
//----------------------------------------------------------------------------//
void StaticVertexBuffer::init(Vertex2D* vertices, u32 vertexCount)
{
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	//Create IDs
	glGenBuffers(1, &_vboID);
	glGenBuffers(1, &_iboID);

	//Specify vertex data
	glBindBuffer(GL_ARRAY_BUFFER, _vboID);

	_vertexCount = vertexCount;
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex2D) * _vertexCount, vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _iboID);

	// Compute indices
	u32 primCount = _vertexCount / 2; // each 4 vertices there are 2 primitives
	_indexCount = primCount * 3;
	u16* indices = new u16[_indexCount];

	size_t index = 0;
	for (u32 i=0; i<_vertexCount; i += 4)
	{
		// there has to be a better way but I'm tired to think
		indices[index++] = i + 0;
		indices[index++] = i + 1;
		indices[index++] = i + 2;
		indices[index++] = i + 2;
		indices[index++] = i + 3;
		indices[index++] = i + 0;
	}

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(u16) * _indexCount, indices, GL_STATIC_DRAW);

	delete [] indices;

	// Reset buffer bindings
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}
//----------------------------------------------------------------------------//
void StaticVertexBuffer::deinit()
{
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glDeleteBuffers(1, &_vboID);
	glDeleteBuffers(1, &_iboID);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}
//----------------------------------------------------------------------------//
void StaticVertexBuffer::render()
{
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glBindBuffer(GL_ARRAY_BUFFER, _vboID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _iboID);

	glVertexPointer(2, GL_FLOAT, sizeof(Vertex2D), BUFFER_OFFSET(0));
	glTexCoordPointer(2, GL_FLOAT, sizeof(Vertex2D), BUFFER_OFFSET(sizeof(f32)*2));

	glDrawElements(GL_TRIANGLES, _indexCount, GL_UNSIGNED_SHORT, BUFFER_OFFSET(0));

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}
//----------------------------------------------------------------------------//
