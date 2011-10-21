#ifndef HE_MESSAGE_H
#define HE_MESSAGE_H
//----------------------------------------------------------------------------//
#include <string>
#include <boost/any.hpp>
//----------------------------------------------------------------------------//
#include "DllExport.h"
//----------------------------------------------------------------------------//
namespace he {
//----------------------------------------------------------------------------//
class ENGINE_API Message
{
public:
	Message(const char *message);
	Message(const char *message, const boost::any &args);

	bool equals(const char *message) const;

	const boost::any& args() const { return args_; }
	template <typename T> T argsAs() const { return boost::any_cast<T>(args_); }

private:
	std::string message_;
	boost::any args_;
};
//----------------------------------------------------------------------------//
} // end namespace he
//----------------------------------------------------------------------------//
#endif // HE_MESSAGE_H
