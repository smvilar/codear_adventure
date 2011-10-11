#include "video/Texture.h"
//----------------------------------------------------------------------------//
#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
//----------------------------------------------------------------------------//
using namespace he;
//----------------------------------------------------------------------------//
Texture::Texture()
: _size(0)
, _id(0)
{
}
//----------------------------------------------------------------------------//
Texture::~Texture()
{
}
//----------------------------------------------------------------------------//
bool Texture::loadFromFile(const char* filename)
{
	sf::Image image;
	if (!image.LoadFromFile(filename))
		return false; // TODO: create a blank image??

	_size.x = image.GetWidth();
	_size.y = image.GetHeight();

	// load the pixels into an OpenGL texture
	loadFromMemory(image.GetPixelsPtr(),
		image.GetWidth(), image.GetHeight(),
		32);

	return true;
}
//----------------------------------------------------------------------------//
bool Texture::loadFromMemory(const void* buffer, u32 width, u32 height, u32 bpp)
{
	GLint internalFormat, format;
	switch (bpp)
	{
	case 8:
		internalFormat = format = GL_LUMINANCE;
		break;
	case 24:
		internalFormat = format = GL_RGB;
		break;
	case 32:
		internalFormat = format = GL_RGBA;
		break;
	default:
		Assert(false, "Texture Pixel Format not supported!");
	}

	// Load texture
	glGenTextures(1, &_id);	
	glBindTexture(GL_TEXTURE_2D, _id);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

	glTexImage2D(
		GL_TEXTURE_2D, 
		0, 
		internalFormat, 
		width, 
		height, 
		0, 
		format, 
		GL_UNSIGNED_BYTE, 
		buffer);

	_size.x = width;
	_size.y = height;

	return true;
}
