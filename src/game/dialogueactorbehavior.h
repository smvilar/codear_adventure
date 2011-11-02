#ifndef DIALOGUEACTORBEHAVIOR_H
#define DIALOGUEACTORBEHAVIOR_H
//----------------------------------------------------------------------------//
#include <hierophantengine.h>
//----------------------------------------------------------------------------//
using namespace he;
//----------------------------------------------------------------------------//
class DialogueActorBehavior : public Behavior
{
public:
	Behavior* clone() const { return new DialogueActorBehavior; }

	void update();
	void handleMessage(const Message &message);

private:
	void added();
	void activate();

private:
	GameObject *answerTextBox_;

	bool showingAnswer_;
	sf::Clock answerClock_;
	u32 answerTime_;

	Attribute *posX_, *posY_, *offsetX_, *offsetY_, *textBoxColor_;

private:
	void setText(const std::string &text);
};
//----------------------------------------------------------------------------//
#endif // DIALOGUEACTORBEHAVIOR_H
