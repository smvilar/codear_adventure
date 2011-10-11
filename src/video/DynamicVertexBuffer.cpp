#include "video/DynamicVertexBuffer.h"
#include "video/glee.h"
//#include <SFML/OpenGL.hpp>
//----------------------------------------------------------------------------//
using namespace he;
//----------------------------------------------------------------------------//
DynamicVertexBuffer::DynamicVertexBuffer()
: _vboID(0)
, _iboID(0)
, _currentTexture(0)
, _vertexBufferSize(0)
, _textureBatchSize(0)
{
}
//----------------------------------------------------------------------------//
DynamicVertexBuffer::~DynamicVertexBuffer()
{
}
//----------------------------------------------------------------------------//
void DynamicVertexBuffer::init()
{
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	//Create IDs
	glGenBuffers(1, &_vboID);
	glGenBuffers(1, &_iboID);

	//Specify vertex data
	glBindBuffer(GL_ARRAY_BUFFER, _vboID);
	glVertexPointer(2, GL_FLOAT, sizeof(Vertex2D), BUFFER_OFFSET(0));
	glTexCoordPointer(2, GL_FLOAT, sizeof(Vertex2D), BUFFER_OFFSET(8));

	// Reset buffer bindings
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);

	// Allocate and initialize arrays
	_vertexBuffer = new Vertex2D[MAX_VERTEX_MEMORY];

	_textureIndexBatch = new u16*[MAX_TEXTURES];
	for(int i = 0; i < MAX_TEXTURES; ++i)
		_textureIndexBatch[i] = new u16[MAX_TEXTURE_INDEXES + 1];

	_indexSize = new u32[MAX_TEXTURES];
	for(int i = 0; i < MAX_TEXTURES; ++i)
		_indexSize[i] = 0;
}
//----------------------------------------------------------------------------//
void DynamicVertexBuffer::deinit()
{
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glDeleteBuffers(1, &_vboID);
	glDeleteBuffers(1, &_iboID);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);

	delete[] _vertexBuffer;
	
	for(int i = 0; i < MAX_TEXTURES; ++i)
		delete[] _textureIndexBatch[i];

	delete[] _textureIndexBatch;

	delete[] _indexSize;
}
//----------------------------------------------------------------------------//
void DynamicVertexBuffer::addVertex(f32 x, f32 y, f32 u, f32 v)
{
	if(!_currentTexture)
		return;

	_vertexBuffer[_vertexBufferSize++] = Vertex2D(x, y, u, v);

	// Automatic indexing for quads. 
	// Itd be cool to have another way of indexing to draw other polygons.
	if(_vertexBufferSize % 4 == 0)
	{
		u32 i = 0;
		for(; i < _textureBatchSize; ++i)
		{
			if(_textureIndexBatch[i][0] == _currentTexture)
				break;
		}

		if(i == _textureBatchSize)
		{
			++_textureBatchSize;
			_textureIndexBatch[i][0] = _currentTexture;
		}

		u32 firstIndex = _vertexBufferSize - 4;

		int indexk = _indexSize[i];
		_textureIndexBatch[i][++indexk] = firstIndex + 0;
		_textureIndexBatch[i][++indexk] = firstIndex + 1;
		_textureIndexBatch[i][++indexk] = firstIndex + 2;
		_textureIndexBatch[i][++indexk] = firstIndex + 2;
		_textureIndexBatch[i][++indexk] = firstIndex + 3;
		_textureIndexBatch[i][++indexk] = firstIndex + 0;

		_indexSize[i] = indexk;
	}
}
//----------------------------------------------------------------------------//
void DynamicVertexBuffer::setCurrTexture(u32 textureID)
{
	_currentTexture = textureID;
}
//----------------------------------------------------------------------------//
void DynamicVertexBuffer::render()
{
	if(!_vertexBufferSize)
		return;

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glBindBuffer(GL_ARRAY_BUFFER, _vboID);
	// Save vertex buffer into graphics memory
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex2D) *_vertexBufferSize, _vertexBuffer, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _iboID);

	for (u32 i = 0; i < _textureBatchSize; ++i)
	{
		int indexk = _indexSize[i];

		glBindTexture(GL_TEXTURE_2D, _textureIndexBatch[i][0]);

		// Save index buffer into graphics memory
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLushort) * indexk, _textureIndexBatch[i] + 1, GL_STATIC_DRAW);

		glVertexPointer(2, GL_FLOAT, sizeof(Vertex2D), BUFFER_OFFSET(0));
		glTexCoordPointer(2, GL_FLOAT, sizeof(Vertex2D), BUFFER_OFFSET(sizeof(f32)*2));

		glDrawElements(GL_TRIANGLES, indexk, GL_UNSIGNED_SHORT, 0);		
	}

	// Reset texture binding
	glBindTexture(GL_TEXTURE_2D, 0);

	// Reset arrays
	_vertexBufferSize = 0;
	_textureBatchSize = 0;
	for(int i = 0; i < MAX_TEXTURES; ++i)
		_indexSize[i] = 0;

	// Reset buffer bindings
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);

	/*
	// Use inmediate mode
	TextureIndexBuffer::iterator it = _indexBuffer.begin();
	int objectk = it->second.size() / 6;
	int objecti = 0;
	for(int i = 0; i < _vertexBuffer.size(); i += 4)
	{
		glBindTexture(GL_TEXTURE_2D, it->first);

		glBegin(GL_QUADS);		
		
		glTexCoord2f(_vertexBuffer[i + 0]._u, _vertexBuffer[i + 0]._v);
		glVertex2f(_vertexBuffer[i + 0]._x, _vertexBuffer[i + 0]._y);
		
		glTexCoord2f(_vertexBuffer[i + 1]._u, _vertexBuffer[i + 1]._v);
		glVertex2f(_vertexBuffer[i + 1]._x, _vertexBuffer[i + 1]._y);
		
		glTexCoord2f(_vertexBuffer[i + 2]._u, _vertexBuffer[i + 2]._v);
		glVertex2f(_vertexBuffer[i + 2]._x, _vertexBuffer[i + 2]._y);
		
		glTexCoord2f(_vertexBuffer[i + 3]._u, _vertexBuffer[i + 3]._v);
		glVertex2f(_vertexBuffer[i + 3]._x, _vertexBuffer[i + 3]._y);		

		glEnd();

		++objecti;

		if(objecti == objectk)
		{
			if(++it == _indexBuffer.end())
				break;

			objectk = it->second.size() / 6;
			objecti = 0;
		}
	}

	_vertexBuffer.clear();
	_indexBuffer.clear();
	*/
}
//----------------------------------------------------------------------------//
