#include "math/Vector2.h"
//----------------------------------------------------------------------------//
using namespace he;
//----------------------------------------------------------------------------//
#ifndef _MSC_VER
template <> const Vector2f Vector2f::ZERO(0.0f);
template <> const Vector2f Vector2f::UNIT_X(1.0f, 0.0f);
template <> const Vector2f Vector2f::UNIT_Y(0.0f, 1.0f);
//----------------------------------------------------------------------------//
template <> const Vector2d Vector2d::ZERO(0.0);
template <> const Vector2d Vector2d::UNIT_X(1.0, 0.0);
template <> const Vector2d Vector2d::UNIT_Y(0.0, 1.0);
//----------------------------------------------------------------------------//
template <> const Vector2u Vector2u::ZERO(0);
template <> const Vector2u Vector2u::UNIT_X(1, 0);
template <> const Vector2u Vector2u::UNIT_Y(0, 1);
//----------------------------------------------------------------------------//
template <> const Vector2i Vector2i::ZERO(0);
template <> const Vector2i Vector2i::UNIT_X(1, 0);
template <> const Vector2i Vector2i::UNIT_Y(0, 1);
//----------------------------------------------------------------------------//
#endif // _MSC_VER
//----------------------------------------------------------------------------//
