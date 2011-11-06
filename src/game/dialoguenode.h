#ifndef HE_DIALOGUENODE_H
#define HE_DIALOGUENODE_H
//----------------------------------------------------------------------------//
#include <string>
#include <vector>
//----------------------------------------------------------------------------//
#include "core/types.h"
//----------------------------------------------------------------------------//
class DialogueNode
{
public:
	// id of the node
	std::string id;
	// the id of the speaker
	std::string speaker;
	// the speech
	std::vector<std::string> speech;
	// possible event that it may send
	std::string event;
	// a link to the next node
	std::string gotoId;
	// do we have to display options?
	bool multipleChoice;

public:
	DialogueNode();

	void nextSpeech();

	const std::string& getCurrentSpeech() const { return speech[currentSpeechIndex_]; }
	bool hasSpeechEnded() const { return currentSpeechIndex_ >= speech.size(); }

private:
	he::u32 currentSpeechIndex_;
};
//----------------------------------------------------------------------------//
#endif // HE_DIALOGUENODE_H
