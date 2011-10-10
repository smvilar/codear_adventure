#ifndef FORAGERS_FONT_H
#define FORAGERS_FONT_H
//----------------------------------------------------------------------------//
#include "DllExport.h"
#include "resource/IResource.h"
//----------------------------------------------------------------------------//
namespace foragers
{
//----------------------------------------------------------------------------//
class FTFontImpl;
//----------------------------------------------------------------------------//
class ENGINE_API Font
	: public IResource
{
public:
	Font();
	virtual ~Font();

	virtual const char* getResourceType() const { return "Font"; }

	virtual bool loadFromFile(const char* filename);

	void setSize(u32 size);
	u32 getSize() const;

	const char* getFamily() const;
	const char* getStyle() const;

	void generateBitmap(const char* text,
		u8* outBuffer, u32 width, u32 height) const;

private:
	u32 _size;

	FTFontImpl* const _pImpl;
};
//----------------------------------------------------------------------------//
typedef boost::shared_ptr<Font> FontPtr;
//----------------------------------------------------------------------------//
} // end namespace foragers
//----------------------------------------------------------------------------//
#endif // __IRESOURCE_H__
