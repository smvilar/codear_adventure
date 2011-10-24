#ifndef HE_ATTRIBUTE_H
#define HE_ATTRIBUTE_H
//----------------------------------------------------------------------------//
#include <boost/any.hpp>
#include "dllexport.h"
//----------------------------------------------------------------------------//
namespace he
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

	friend class WorldSerializer;
};
//----------------------------------------------------------------------------//
} // end namespace he
//----------------------------------------------------------------------------//
#endif // HE_ATTRIBUTE_H
