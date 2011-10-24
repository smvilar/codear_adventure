#ifndef HE_dllexport_H
#define HE_dllexport_H
//----------------------------------------------------------------------------//
// For the DLL library.
#ifdef BUILD_DLL
// Disable warning for template exported class
#pragma warning(disable:4251)
#ifdef DLL_EXPORT
#	define ENGINE_API __declspec(dllexport)
// For a client of the DLL library.
#else // DLL_EXPORT
#	define ENGINE_API __declspec(dllimport)
#endif // DLL_EXPORT
#else // BUILD_DLL
#	define ENGINE_API
#endif // BUILD_DLL
//----------------------------------------------------------------------------//
#endif // HE_dllexport_H
