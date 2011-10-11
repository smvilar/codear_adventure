#ifndef FORAGERS_ASSERT_H
#define FORAGERS_ASSERT_H
//----------------------------------------------------------------------------//
#include <cassert>
//----------------------------------------------------------------------------//
namespace he
{
//----------------------------------------------------------------------------//
#ifdef _DEBUG

// Assert with more information
#	define Assert(condition, description) assert((condition) && description)
// Assert in compile-time
#	define CAssert(condition) typedef char _C_ASSERT_[(condition)?1:-1]

#else // _DEBUG

#	define Assert(condition, description)
#	define CAssert(condition)

#endif // _DEBUG
//----------------------------------------------------------------------------//
} // end namespace he
//----------------------------------------------------------------------------//
#endif // FORAGERS_ASSERT_H
