#ifndef HE_DIALOGUE_H
#define HE_DIALOGUE_H
//----------------------------------------------------------------------------//
#include <vector>
//----------------------------------------------------------------------------//
#include "dialoguenode.h"
//----------------------------------------------------------------------------//
class Dialogue
{
public:
	Dialogue() : hasEnded_(false) {}

	bool parse(const std::string &text);

	DialogueNode* getNodeById(const char *id);
	DialogueNode* getCurrentNode() { return currentNode_; }

	void selectAnswer(size_t index);
	bool isValidAnswer(size_t index) const { return index < currentNode_->answers.size(); }
	bool hasEnded() const { return hasEnded_; }

private:
	typedef std::vector<DialogueNode*> DialogueNodeVector;
	DialogueNodeVector dialogueNodes_;

	DialogueNode *currentNode_;
	bool hasEnded_;
};
//----------------------------------------------------------------------------//
#endif // HE_DIALOGUE_H
