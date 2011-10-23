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

	virtual void update();

private:
	virtual void activate();

private:
	Dialogue dialogue_;
	he::Attribute *textAttr_;

	bool displayingAnswers_;

private:
	void updateText(const std::string &text);
	void displayAnswers();
};
//----------------------------------------------------------------------------//
#endif // DIALOGUECONTROLBEHAVIOR_H
