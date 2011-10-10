#include "resource/Font.h"
//----------------------------------------------------------------------------//
#include <iostream>
#include <string>
//----------------------------------------------------------------------------//
#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_GLYPH_H
//----------------------------------------------------------------------------//
#include "core/Assert.h"
//----------------------------------------------------------------------------//
// TODO: put it in another place!
FT_Library ftLib;
//----------------------------------------------------------------------------//
namespace foragers
{
//----------------------------------------------------------------------------//
// The only thing this class do is wrap the FT_Face handle from freetype lib
// so we don't have to include the ft lib headers in Font.h :)
//----------------------------------------------------------------------------//
class FTFontImpl
{
public:
	FT_Face face;

	void drawBitmap(u8* outBitmap, s32 maxWidth, s32 maxHeight,
		FT_Bitmap* inBitmap, FT_Int x, FT_Int y)
	{
		s32 i, j, p, q;
		s32 xMax = x + inBitmap->width;
		s32 yMax = y + inBitmap->rows;

		for (i=x, p=0; i<xMax; ++i, ++p)
		{
			for (j=y, q=0; j<yMax; ++j, ++q)
			{
				if (i >= maxWidth || j >= maxHeight)
					continue;

				s32 index = j*maxWidth+i;
				Assert((index < maxWidth * maxHeight), "Array out of bounds");
				outBitmap[index] |= inBitmap->buffer[q * inBitmap->width + p];
			}
		}
	}
};
//----------------------------------------------------------------------------//
} // end namespace foragers
//----------------------------------------------------------------------------//
using namespace foragers;
//----------------------------------------------------------------------------//
Font::Font() : _pImpl(new FTFontImpl)
{
	// TODO: put it in another place!
	FT_Error error = FT_Init_FreeType(&ftLib);
	if (error)
	{
		std::cout << "error initializing freetype" << std::endl;
	}
}
//----------------------------------------------------------------------------//
Font::~Font()
{
	delete _pImpl;
}
//----------------------------------------------------------------------------//
bool Font::loadFromFile(const char* filename)
{
	FT_Error error = FT_New_Face(ftLib, filename, 0, &_pImpl->face);
	Assert(error == FT_Err_Ok, "Error creating font");

	setSize(12); // set a default size (needed)

	return true;
}
//----------------------------------------------------------------------------//
void Font::setSize(u32 size)
{
	const u32 dpi = 72; // TODO: check later what to do with this
	_size = size;
	FT_Error error = FT_Set_Char_Size(_pImpl->face, 0, size << 6, dpi, dpi);
	Assert(error == FT_Err_Ok, "Error setting font size");
}
//----------------------------------------------------------------------------//
u32 Font::getSize() const
{
	return _size;
}
//----------------------------------------------------------------------------//
const char* Font::getFamily() const
{
	return _pImpl->face->family_name;
}
//----------------------------------------------------------------------------//
const char* Font::getStyle() const
{
	return _pImpl->face->style_name;
}
//----------------------------------------------------------------------------//
void Font::generateBitmap(const char* text,
						  u8* outBuffer, u32 width, u32 height) const
{
	using std::string;
	string strText(text);

	FT_Face face = _pImpl->face;
	FT_GlyphSlot slot = face->glyph;
	FT_UInt glyphIndex;
	FT_UInt prevGlyphIndex = 0; // for kerning

	int error;
	FT_Vector pen;
	pen.x = 0;
	pen.y = 0;

	const bool useKerning = true;

	for (size_t i=0; i<strText.size(); ++i)
	{
		glyphIndex = FT_Get_Char_Index(face, strText[i]);

		// load glyph image into the slot (erase previous one)
		error = FT_Load_Glyph(face, glyphIndex, FT_LOAD_RENDER);
		if (error)
			continue; // ignore error

		// apply kerning
		if (useKerning && prevGlyphIndex > 0)
		{
			FT_Vector delta;
			FT_Get_Kerning(face, prevGlyphIndex, glyphIndex,
				FT_KERNING_DEFAULT, &delta);
			pen.x += delta.x >> 6;
		}

		// adjust to box
		if (pen.x + (slot->metrics.width >> 6) > (s32)width)
		{
			pen.x = 0;
			pen.y += slot->metrics.vertAdvance >> 6;
		}
		
		// now, draw!
		FT_Glyph glyph;
		FT_Get_Glyph(slot, &glyph);
		error = FT_Glyph_To_Bitmap(&glyph, FT_RENDER_MODE_NORMAL, &pen, 0);
		if (!error)
		{
			FT_BitmapGlyph bitmap = (FT_BitmapGlyph)glyph;
			FT_Int y = pen.y - bitmap->top;
			if (y < 0) // weird height adjustment
			{
				pen.y -= y;
				y = 0;
			}
			
			_pImpl->drawBitmap(outBuffer, width, height,
				/*&slot->bitmap*/&bitmap->bitmap, pen.x, y);
		}

		// increment the pen position
		pen.x += slot->advance.x >> 6;

		prevGlyphIndex = glyphIndex;
	}
}
//----------------------------------------------------------------------------//
