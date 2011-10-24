#ifndef HE_TEXTINPUTBEHAVIOR_H
#define HE_TEXTINPUTBEHAVIOR_H
//----------------------------------------------------------------------------//
#include <string>
//----------------------------------------------------------------------------//
#include "dllexport.h"
#include "gameobject/behavior.h"
//----------------------------------------------------------------------------//
namespace he {
//----------------------------------------------------------------------------//
class Message;
class Attribute;
//----------------------------------------------------------------------------//
class ENGINE_API TextInputBehavior : public Behavior
{
public:
	virtual Behavior* clone() const { return new TextInputBehavior; }

	virtual void handleMessage(const Message &message);

private:
	virtual void added();

private:
	Attribute *textAttr_;

	void updateText(const std::string &str);
	void backspace();
};
//----------------------------------------------------------------------------//
} // end namespace he
//----------------------------------------------------------------------------//
#endif // HE_TEXTINPUTBEHAVIOR_H
