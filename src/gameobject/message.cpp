#include "gameobject/message.h"
//----------------------------------------------------------------------------//
using namespace he;
//----------------------------------------------------------------------------//
Message::Message(const char *message)
: message_(message)
{
	// ...
}
//----------------------------------------------------------------------------//
Message::Message(const char *message, const boost::any &args)
: message_(message)
, args_(args)
{
	// ...
}
//----------------------------------------------------------------------------//
bool Message::equals(const char *message) const
{
	return message_.compare(message) == 0;
}
//----------------------------------------------------------------------------//
