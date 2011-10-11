#ifndef HE_BASEOBJECT_H
#define HE_BASEOBJECT_H
//----------------------------------------------------------------------------//
#include <string>
#include "DllExport.h"
#include "Types.h"
//----------------------------------------------------------------------------//
namespace he
{
//----------------------------------------------------------------------------//
class ENGINE_API BaseObject
{
public:
	BaseObject() {}
	virtual ~BaseObject() {}

	void setName(const char* name);
	const std::string& getName() const;

protected:
	std::string m_name;
};
//----------------------------------------------------------------------------//
#include "BaseObject.inl"
//----------------------------------------------------------------------------//
} // end namespace he
//----------------------------------------------------------------------------//
#endif // HE_BASEOBJECT_H
