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
	struct Answer
	{
		std::string answer;
		std::string gotoId;
		std::string event;

		Answer(const std::string &answer, const std::string &gotoId,
			   const std::string &event)
			: answer(answer), gotoId(gotoId), event(event)
		{
			// ...
		}
	};

public:
	std::string id;
	std::vector<std::string> speech;
	std::vector<Answer> answers;

public:
	DialogueNode();

	void nextSpeech();

	const std::string& getCurrentSpeech() const { return speech[currentSpeechIndex_]; }
	bool hasSpeechEnded() const { return currentSpeechIndex_ == speech.size() - 1; }
	const std::string& getAnswer(size_t index) const { return answers[index].answer; }
	size_t getAnswerQuantity() const { return answers.size(); }

	const std::string& getNextDialogueNodeId(size_t answerIndex) const { return answers[answerIndex].gotoId; }
	const std::string& getAnswerEvent(size_t answerIndex) const { return answers[answerIndex].event; }

private:
	he::u32 currentSpeechIndex_;
};
//----------------------------------------------------------------------------//
#endif // HE_DIALOGUENODE_H
