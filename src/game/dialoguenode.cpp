#include "game/dialoguenode.h"
//----------------------------------------------------------------------------//
DialogueNode::DialogueNode()
: currentSpeechIndex_(0)
{
	//
}
//----------------------------------------------------------------------------//
void DialogueNode::nextSpeech()
{
	++currentSpeechIndex_;
	if (currentSpeechIndex_ >= speech.size())
		currentSpeechIndex_ = speech.size() - 1;
}
//----------------------------------------------------------------------------//
