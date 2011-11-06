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

	virtual void handleMessage(const Message &message);

private:
	virtual void activate();

private:
	Dialogue dialogue_;

	bool displayingAnswers_; // for the option list
	bool showingSpeech_; // for the actors with speech box

private:
	void nextSpeech();
	void displayAnswers();
	void selectAnswer(size_t index);

	GameObject* getSpeaker();
};
//----------------------------------------------------------------------------//
#endif // DIALOGUECONTROLBEHAVIOR_H
