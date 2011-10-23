#include "game/dialogue.h"
//----------------------------------------------------------------------------//
#include <fstream>
//----------------------------------------------------------------------------//
#include "json/json.h"
//----------------------------------------------------------------------------//
bool Dialogue::parse(const char *filename)
{
	Json::Reader reader;
	Json::Value root;

	std::ifstream ifs(filename);

	if (!reader.parse(ifs, root))
	{
		std::cerr << "Error parsing dialogue " << filename << ": " << std::endl
				  << reader.getFormatedErrorMessages() << std::endl;
		return false;
	}

	for (size_t i = 0; i < root.size(); ++i)
	{
		const Json::Value &jsDNode = root[i];

		DialogueNode *dialogueNode = new DialogueNode;
		dialogueNode->id = jsDNode["id"].asCString();

		const Json::Value &jsSpeech = jsDNode["speech"];
		for (size_t j = 0; j < jsSpeech.size(); ++j)
		{
			dialogueNode->speech.push_back(jsSpeech[j].asCString());
		}

		const Json::Value &jsAnswers = jsDNode["answers"];
		for (size_t j = 0; j < jsAnswers.size(); ++j)
		{
			const Json::Value &jsAns = jsAnswers[j];
			const char *ans = jsAns["answer"].asCString();
			const char *gotoId = jsAns["goto"].asCString();
			dialogueNode->answers.push_back(DialogueNode::Answer(ans, gotoId));
		}

		dialogueNodes_.push_back(dialogueNode);
	}

	currentNode_ = dialogueNodes_[0];

	return true;
}
//----------------------------------------------------------------------------//
struct EqualIds
{
	std::string id;
	EqualIds(const char *id) : id(id) {}
	bool operator()(DialogueNode *node) { return node->id == id; }
};
//----------------------------------------------------------------------------//
DialogueNode* Dialogue::getNodeById(const char *id)
{
	DialogueNodeVector::iterator it =
		std::find_if(dialogueNodes_.begin(), dialogueNodes_.end(), EqualIds(id));
	return it != dialogueNodes_.end() ? *it : 0;
}
//----------------------------------------------------------------------------//