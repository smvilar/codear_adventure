#ifndef DIALOGUECONTROLBEHAVIOR_H
#define DIALOGUECONTROLBEHAVIOR_H
//----------------------------------------------------------------------------//
#include "hierophantengine.h"
#include "dialogue.h"
//----------------------------------------------------------------------------//
using namespace he;
//----------------------------------------------------------------------------//
class DialogueControlBehavior : public Behavior
{
public:
	virtual Behavior* clone() const { return new DialogueControlBehavior; }

	virtual void handleMessage(const Message &message);

private:
	virtual void activate();

private:
	Dialogue dialogue_;
	Attribute *textAttr_;

	bool displayingAnswers_;

private:
	void updateText(const std::string &text);
	void displayAnswers();

	void nextSpeech();
	void selectAnswer(size_t index);
};
//----------------------------------------------------------------------------//
#endif // DIALOGUECONTROLBEHAVIOR_H
