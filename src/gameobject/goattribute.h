#ifndef FORAGERS_GOATTRIBUTE_H
#define FORAGERS_GOATTRIBUTE_H
//----------------------------------------------------------------------------//
#include <boost/any.hpp>
#include "DllExport.h"
//----------------------------------------------------------------------------//
namespace foragers
{
//----------------------------------------------------------------------------//
class ENGINE_API Attribute
{
public:
	Attribute(boost::any value);
	Attribute* clone() const;

	template<typename T>
	T getValue() const
	{
		return boost::any_cast<T>(_value);
	}

	template<typename T>
	void setValue(T value)
	{
		_value = value;
	}

private:
	boost::any _value;
};
//----------------------------------------------------------------------------//
} // end namespace foragers
//----------------------------------------------------------------------------//
#endif // FORAGERS_GOATTRIBUTE_H
