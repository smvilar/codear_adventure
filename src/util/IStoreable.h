#ifndef FORAGERS_ISTOREABLE_H
#define FORAGERS_ISTOREABLE_H
//----------------------------------------------------------------------------//
#include <string>
#include <rapidxml.hpp>
//----------------------------------------------------------------------------//
#include "DllExport.h"
#include "util/Util.h"
//----------------------------------------------------------------------------//
namespace foragers
{
//----------------------------------------------------------------------------//
class ENGINE_API IStoreable
{
public:
	virtual ~IStoreable() {}

	virtual bool load(const char* filename) = 0;
	virtual bool save(const char* filename) = 0;

/// Helper methods
protected:
	template <typename Type>
	rapidxml::xml_node<>* createNode(rapidxml::xml_document<>& doc,
		const char* name, const Type& value);
	template <typename Type>
	void getValueFromNode(rapidxml::xml_node<>* node, Type& value);
};
//----------------------------------------------------------------------------//
template <typename Type>
rapidxml::xml_node<>* IStoreable::createNode(rapidxml::xml_document<>& doc,
											 const char* name,
											 const Type& value)
{
	using namespace rapidxml;

	const char* strValue = doc.allocate_string(toString(value).c_str());
	return doc.allocate_node(node_element, name, strValue);
}
//----------------------------------------------------------------------------//
template <typename Type>
void IStoreable::getValueFromNode(rapidxml::xml_node<>* node, Type& value)
{
	using namespace rapidxml;

	value = fromString<Type>(node->value());
}
//----------------------------------------------------------------------------//
} // end namespace foragers
//----------------------------------------------------------------------------//
#endif // FORAGERS_ISTOREABLE_H
//----------------------------------------------------------------------------//
