#ifndef HE_MESSAGE_H
#define HE_MESSAGE_H
//----------------------------------------------------------------------------//
#include <string>
#include <any>
//----------------------------------------------------------------------------//
#include "dllexport.h"
//----------------------------------------------------------------------------//
namespace he {
//----------------------------------------------------------------------------//
class ENGINE_API Message
{
public:
	Message(const std::string &message) : message_(message) {}
	Message(const char *message) : message_(message) {}
	Message(const std::string &message, const std::any &args) :
		message_(message), args_(args) {}
	Message(const char *message, const std::any &args) :
		message_(message), args_(args) {}

	bool equals(const char *message) const;

	const std::any& args() const { return args_; }
	template <typename T> T argsAs() const { return std::any_cast<T>(args_); }

	const std::string& getMessage() const { return message_; }

private:
	std::string message_;
	std::any args_;
};
//----------------------------------------------------------------------------//
} // end namespace he
//----------------------------------------------------------------------------//
#endif // HE_MESSAGE_H
