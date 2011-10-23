#ifndef DIALOGUECONTROLBEHAVIOR_H
#define DIALOGUECONTROLBEHAVIOR_H
//----------------------------------------------------------------------------//
#include "hierophantengine.h"
#include "dialogue.h"
//----------------------------------------------------------------------------//
class DialogueControlBehavior : public he::Behavior
{
public:
	virtual he::Behavior* clone() const { return new DialogueControlBehavior; }

	virtual void handleMessage(const he::Message &message);

private:
	virtual void activate();

private:
	Dialogue dialogue_;
	he::Attribute *textAttr_;

	bool displayingAnswers_;

private:
	void updateText(const std::string &text);
	void displayAnswers();

	void nextSpeech();
	void selectAnswer(size_t index);
};
//----------------------------------------------------------------------------//
#endif // DIALOGUECONTROLBEHAVIOR_H
