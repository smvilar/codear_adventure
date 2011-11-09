#include "databasebehavior.h"
//----------------------------------------------------------------------------//
struct DBEntry {
	std::string key;
	std::string info;
};
//----------------------------------------------------------------------------//
const DBEntry dbEntries[] =
{
	{ "Schulman Researchs", "Prestigiosa empresa de 50 años de existencia. Realiza investigaciones biológicas." },
	{ "codearxis v9", "Virus peligroso." },
	{ "Matthew Smith", "Científico.\nEdad: 29 años.\nEstado civil: casado.\nHijos: ninguno." },
	{ "Jeffrey Remington", "Seguridad.\nEdad: 54 años.\nEstado civil: casado.\nHijos: 1." },
	{ "Carl Schultz", "Técnico.\nEdad: 31 años.\nEstado civil: soltero.\nHijos: ninguno." },
	{ "David Wright", "Científico.\nEdad: 42 años.\nEstado civil: casado.\nHijos: 2." },
	{ "George Ingram", "Científico.\nEdad: 34 años.\nEstado civil: soltero.\nHijos: ninguno." },
	{ "Richard Solomon", "Negociador. Ha resuelto los casos más complicados."}
};
//----------------------------------------------------------------------------//
void DatabaseBehavior::activate()
{
	displayingResult_ = false;
	databaseInput_ = pWorld_->createObject("DatabaseInput");
}
//----------------------------------------------------------------------------//
void DatabaseBehavior::handleMessage(const Message &message)
{
	if (message.equals("database_prepare_input"))
	{
		pOwner_->broadcast(Message("play_animation", std::string("console")));
		pWorld_->addObject(databaseInput_);
	}
	else if (message.equals("text_input"))
	{
		std::string text = message.argsAs<std::string>();
		if (displayingResult_)
		{
			displayingResult_ = false;
			text.erase(text.begin(), text.end()-1);
			updateText(text);
		}
		else if (text.length() > 20) // too long text
		{
			updateText(text.erase(text.length()-1));
		}

		if (text[text.length()-1] == '\n') // pressed Return
		{
			displayingResult_ = true;
			searchDatabase(text.erase(text.length()-1));
		}
	}
	else if (message.equals("database_close_input"))
	{
		pOwner_->broadcast(Message("play_animation", std::string("static")));
		pWorld_->removeObject(databaseInput_);
	}
}
//----------------------------------------------------------------------------//
void DatabaseBehavior::searchDatabase(const std::string &text)
{
	// the maximum length of a string to check (all exceeding chars are ignored)
	const size_t maxLen = 4;
	std::string lowerText;
	for (size_t i=0; i<std::min(maxLen,text.length()); ++i)
		lowerText.push_back(std::tolower(text[i], std::locale()));

	size_t numDBEntries = sizeof(dbEntries) / sizeof(DBEntry);
	std::string info = "Not found";
	for (size_t i = 0; i < numDBEntries; ++i)
	{
		std::string lowerEntry;
		for (size_t j=0; j<std::min(maxLen,dbEntries[i].key.length()); ++j)
			lowerEntry.push_back(std::tolower(dbEntries[i].key[j], std::locale()));

		if (lowerText == lowerEntry)
		{
			info = dbEntries[i].key + "\n\n" + dbEntries[i].info;
			// check win condition
			if (dbEntries[i].key == "David Wright")
			{
				pWorld_->broadcast(Message("trigger_condition", std::string("david_found")));
			}
			break;
		}
	}
	updateText(info);
}
//----------------------------------------------------------------------------//
void DatabaseBehavior::updateText(const std::string &text)
{
	(*databaseInput_)["text"]->set(text);
	databaseInput_->broadcast(Message("update_text"));
}
//----------------------------------------------------------------------------//
