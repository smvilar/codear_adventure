#ifndef PHONECONTROLLERBEHAVIOR_H
#define PHONECONTROLLERBEHAVIOR_H
//----------------------------------------------------------------------------//
#include <hierophantengine.h>
//----------------------------------------------------------------------------//
using namespace he;
//----------------------------------------------------------------------------//
class PhoneControllerBehavior : public Behavior
{
public:
	PhoneControllerBehavior();
	virtual Behavior *clone() const { return new PhoneControllerBehavior; }

	virtual void handleMessage(const Message &message);

private:
	virtual void added();

private:
	struct Conversation
	{
		u32 state;
		std::vector<std::string> filenames;

		const std::string& step()
		{
			const std::string &text = filenames[state];
			if (state < filenames.size() - 1)
				++state;
			return text;
		}
	};

	typedef std::map<std::string, Conversation> ConversationStates;
	ConversationStates conversationStates_;

	Attribute *dialogueFilenameAttr_;

	bool conversationStarted_;
};
//----------------------------------------------------------------------------//
#endif // PHONECONTROLLERBEHAVIOR_H
