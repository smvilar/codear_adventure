#include "game/dialoguenode.h"
//----------------------------------------------------------------------------//
DialogueNode::DialogueNode()
: multipleChoice(false)
, currentSpeechIndex_(0)
{
	//
}
//----------------------------------------------------------------------------//
void DialogueNode::nextSpeech()
{
	++currentSpeechIndex_;
}
//----------------------------------------------------------------------------//
