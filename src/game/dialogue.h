#ifndef HE_DIALOGUE_H
#define HE_DIALOGUE_H
//----------------------------------------------------------------------------//
#include <vector>
//----------------------------------------------------------------------------//
#include <hierophantengine.h>
//----------------------------------------------------------------------------//
#include "dialoguenode.h"
//----------------------------------------------------------------------------//
using namespace he;
//----------------------------------------------------------------------------//
class Dialogue
{
public:
	Dialogue() : hasEnded_(false) {}

	bool parse(const std::string &text);

	DialogueNode* getNodeById(const std::string &id);
	DialogueNode* getCurrentNode() { return currentNode_; }

	void next();

	// Selects the specified answer
	// Returns a custom event that it may have
	//std::string selectAnswer(size_t index);

	//bool isValidAnswer(size_t index) const { return index < currentNode_->answers.size(); }
	bool hasEnded() const { return hasEnded_; }

	static u32 getSpeechTime(const std::string &text);

private:
	typedef std::vector<DialogueNode*> DialogueNodes;
	DialogueNodes dialogueNodes_;

	DialogueNode *currentNode_;
	bool hasEnded_;
};
//----------------------------------------------------------------------------//
#endif // HE_DIALOGUE_H
