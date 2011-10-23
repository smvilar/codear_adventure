#ifndef HE_DIALOGUENODE_H
#define HE_DIALOGUENODE_H
//----------------------------------------------------------------------------//
#include <string>
#include <vector>
//----------------------------------------------------------------------------//
class DialogueNode
{
public:
	struct Answer
	{
		std::string answer;
		std::string gotoId;

		Answer(const std::string &answer, const std::string &gotoId)
			: answer(answer), gotoId(gotoId)
		{
			// ...
		}
	};

	std::string id;
	std::vector<std::string> speech;
	std::vector<Answer> answers;
};
//----------------------------------------------------------------------------//
#endif // HE_DIALOGUENODE_H
