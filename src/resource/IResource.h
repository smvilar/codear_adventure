#ifndef FORAGERS_IRESOURCE_H
#define FORAGERS_IRESOURCE_H
//----------------------------------------------------------------------------//
#include <boost/smart_ptr/shared_ptr.hpp>
//----------------------------------------------------------------------------//
#include "DllExport.h"
#include "core/Types.h"
//----------------------------------------------------------------------------//
namespace he
{
//----------------------------------------------------------------------------//
class ENGINE_API IResource
{
public:
	virtual ~IResource() {}
	virtual const char* getResourceType() const = 0;

	// returns true if succesful, false otherwise
	virtual bool loadFromFile(const char* filename) = 0;
};
//----------------------------------------------------------------------------//
typedef boost::shared_ptr<IResource> IResourcePtr;
//----------------------------------------------------------------------------//
} // end namespace he
//----------------------------------------------------------------------------//
#endif // FORAGERS_IRESOURCE_H
