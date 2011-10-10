#include "gameobject/goattribute.h"
//----------------------------------------------------------------------------//
using namespace foragers;
//----------------------------------------------------------------------------//
GOAttribute::GOAttribute(boost::any value)
	: _value(value)
{
	// ...
}
//----------------------------------------------------------------------------//
GOAttribute* GOAttribute::clone() const
{
	return new GOAttribute(_value);
}
//----------------------------------------------------------------------------//
