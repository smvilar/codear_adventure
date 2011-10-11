#ifndef HE_UTIL_H
#define HE_UTIL_H
//----------------------------------------------------------------------------//
#include <sstream>
#include "DllExport.h"
#include "core/Types.h"
//----------------------------------------------------------------------------//
namespace he
{
//----------------------------------------------------------------------------//
template <class T>
inline std::string toString(const T& t)
{
	std::stringstream ss;
	ss << t;
	return ss.str();
}
//----------------------------------------------------------------------------//
template <class T>
inline T fromString(const char* str)
{
	std::stringstream ss;
	ss << str;
	T value;
	ss >> value;
	return value;
}
//----------------------------------------------------------------------------//
} // end namespace he
//----------------------------------------------------------------------------//
#endif // HE_UTIL_H
//----------------------------------------------------------------------------//
