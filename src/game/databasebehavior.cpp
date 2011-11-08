#include "databasebehavior.h"
//----------------------------------------------------------------------------//
void DatabaseBehavior::activate()
{
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
}
//----------------------------------------------------------------------------//