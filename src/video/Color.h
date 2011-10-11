#ifndef FORAGERS_COLOR_H
#define FORAGERS_COLOR_H
//----------------------------------------------------------------------------//
#include "core/Types.h"
//----------------------------------------------------------------------------//
namespace he
{
//----------------------------------------------------------------------------//
class Color
{
public:
	Color(): argb(0) {}
	Color(u32 argb): argb(argb) {}
	Color(u8 a, u8 r, u8 g, u8 b): a(a), r(r), g(g), b(b) {}
	Color(u8 r, u8 g, u8 b): a(0xff), r(r), g(g), b(b) {}

	union
	{
		struct
		{
			u8 b;
			u8 g;
			u8 r;
			u8 a;
		};
		u32 argb;
	};

	static const Color WHITE;
	static const Color BLACK;
	static const Color RED;
	static const Color GREEN;
	static const Color BLUE;
	static const Color MAGENTA;
	static const Color YELLOW;
};
//----------------------------------------------------------------------------//
} // end namespace he
//----------------------------------------------------------------------------//
#endif // FORAGERS_COLOR_H
