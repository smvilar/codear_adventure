#ifndef HE_ATTRIBUTE_H
#define HE_ATTRIBUTE_H
//----------------------------------------------------------------------------//
#include <any>
#include "dllexport.h"
//----------------------------------------------------------------------------//
namespace he
{
//----------------------------------------------------------------------------//
class ENGINE_API Attribute
{
public:
	Attribute(const std::any& value);

	template<typename T>
	T get() const
	{
		return std::any_cast<T>(value_);
	}

	template<typename T>
	void set(T value)
	{
		value_ = value;
	}

private:
	std::any value_;

	friend class WorldSerializer;
};
//----------------------------------------------------------------------------//
} // end namespace he
//----------------------------------------------------------------------------//
#endif // HE_ATTRIBUTE_H
