#ifndef FORAGERS_TEXTURE_H
#define FORAGERS_TEXTURE_H
//----------------------------------------------------------------------------//
#include "DllExport.h"
#include "resource/IResource.h"
#include "math/Vector2.h"
//----------------------------------------------------------------------------//
namespace foragers
{
//----------------------------------------------------------------------------//
class ENGINE_API Texture
	: public IResource
{
public:
	Texture();
	virtual ~Texture();

	virtual const char* getResourceType() const { return "Texture"; }

	// returns true if succesful, false otherwise
	virtual bool loadFromFile(const char* filename);

	bool loadFromMemory(const void* buffer, u32 width, u32 height, u32 bpp);

	const Vector2u& getSize() const;
	u32 getID() const;

private:
	Vector2u _size;
	u32 _id;
};
//----------------------------------------------------------------------------//
#include "Texture.inl"
//----------------------------------------------------------------------------//
typedef boost::shared_ptr<Texture> TexturePtr;
//----------------------------------------------------------------------------//
} // end namespace foragers
//----------------------------------------------------------------------------//
#endif // FORAGERS_TEXTURE_H
