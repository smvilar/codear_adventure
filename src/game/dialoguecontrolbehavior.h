#ifndef DIALOGUECONTROLBEHAVIOR_H
#define DIALOGUECONTROLBEHAVIOR_H
//----------------------------------------------------------------------------//
#include <hierophantengine.h>
//----------------------------------------------------------------------------//
#include "dialogue.h"
//----------------------------------------------------------------------------//
using namespace he;
//----------------------------------------------------------------------------//
class DialogueControlBehavior : public Behavior
{
public:
	virtual Behavior* clone() const { return new DialogueControlBehavior; }

	virtual void update();
	virtual void handleMessage(const Message &message);

private:
	virtual void activate();

private:
	Dialogue dialogue_;
	Attribute *textAttr_;
	MouseUtil *mouseUtil_;

	bool displayingAnswers_; // for the option list
	bool showingAnswer_; // for the main actor's speech

	sf::Clock textClock_;
	u32 textTime_;

private:
	void updateText(const std::string &text);

	void nextSpeech();
	void displayAnswers();
	void selectAnswer(size_t index);
};
//----------------------------------------------------------------------------//
#endif // DIALOGUECONTROLBEHAVIOR_H
