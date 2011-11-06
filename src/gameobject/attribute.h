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

	template<typename T>
	T get() const
	{
		return boost::any_cast<T>(_value);
	}

	template<typename T>
	void set(T value)
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
