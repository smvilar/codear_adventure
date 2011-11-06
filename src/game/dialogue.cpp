#include "game/dialogue.h"
//----------------------------------------------------------------------------//
#include <fstream>
#include <algorithm>
//----------------------------------------------------------------------------//
#include "json/json.h"
//----------------------------------------------------------------------------//
bool Dialogue::parse(const std::string &text)
{
	Json::Reader reader;
	Json::Value root;

	if (!reader.parse(text, root))
	{
		std::cerr << "Error parsing dialogue: "
				  << reader.getFormatedErrorMessages() << std::endl;
		return false;
	}

	for (size_t i = 0; i < root.size(); ++i)
	{
		const Json::Value &jsDNode = root[i];

		DialogueNode *dialogueNode = new DialogueNode;
		dialogueNode->id = jsDNode["id"].asString();
		dialogueNode->speaker = jsDNode["speaker"].asString();

		const Json::Value &jsSpeech = jsDNode["speech"];
		for (size_t j = 0; j < jsSpeech.size(); ++j)
			dialogueNode->speech.push_back(jsSpeech[j].asString());

		dialogueNode->event = jsDNode["event"].asString();
		dialogueNode->gotoId = jsDNode["goto"].asString();
		dialogueNode->multipleChoice = jsDNode["multipleChoice"].asBool();

		dialogueNodes_.push_back(dialogueNode);
	}

	currentNode_ = dialogueNodes_[0];

	return true;
}
//----------------------------------------------------------------------------//
struct EqualIds
{
	std::string id;
	EqualIds(const std::string &id) : id(id) {}
	bool operator()(DialogueNode *node) { return node->id == id; }
};
//----------------------------------------------------------------------------//
DialogueNode* Dialogue::getNodeById(const std::string &id)
{
	DialogueNodes::iterator it =
		std::find_if(dialogueNodes_.begin(), dialogueNodes_.end(), EqualIds(id));
	return it != dialogueNodes_.end() ? *it : 0;
}
//----------------------------------------------------------------------------//
//std::string Dialogue::selectAnswer(size_t index)
//{
//	const std::string &gotoId = currentNode_->getNextDialogueNodeId(index);
//	const std::string &event = currentNode_->getAnswerEvent(index);
//	if (gotoId == "end")
//		hasEnded_ = true;
//	else
//		currentNode_ = getNodeById(gotoId.c_str());

//	return event;
//}
//----------------------------------------------------------------------------//
u32 Dialogue::getSpeechTime(const std::string &text)
{
	return std::max<int>(1000, text.length() * 50);
}
//----------------------------------------------------------------------------//
void Dialogue::next()
{
	if (currentNode_->gotoId == "end")
		hasEnded_ = true;
	else
		currentNode_ = getNodeById(currentNode_->gotoId);
}
//----------------------------------------------------------------------------//
