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
	void deactivate();

private:
	sf::Font font_;
	sf::Text text_;

	bool showingAnswer_;
	sf::Clock answerClock_;

	Attribute *posX_, *posY_, *offsetX_, *offsetY_;
};
//----------------------------------------------------------------------------//
#endif // DIALOGUEACTORBEHAVIOR_H
