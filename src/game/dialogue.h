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
	bool parse(const char *filename);

	DialogueNode* getNodeById(const char *id);
	DialogueNode* getCurrentNode() { return currentNode_; }

	void selectAnswer(size_t index);

private:
	typedef std::vector<DialogueNode*> DialogueNodeVector;
	DialogueNodeVector dialogueNodes_;

	DialogueNode *currentNode_;
};
//----------------------------------------------------------------------------//
#endif // HE_DIALOGUE_H
