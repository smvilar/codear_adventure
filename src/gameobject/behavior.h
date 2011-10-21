#ifndef HE_BEHAVIOR_H
#define HE_BEHAVIOR_H
//----------------------------------------------------------------------------//
#include "DllExport.h"
//----------------------------------------------------------------------------//
namespace he
{
//----------------------------------------------------------------------------//
class GameObject;
class World;
class Message;
//----------------------------------------------------------------------------//
class ENGINE_API Behavior
{
public:
	Behavior();
	virtual ~Behavior() {}

	virtual void update();
	virtual void handleMessage(const Message &message);

	virtual Behavior* clone() const = 0;

protected:
	virtual void added() {}
	virtual void removed() {}
	virtual void activate() {}
	virtual void deactivate() {}

protected:
	GameObject *pOwner_;
	World *pWorld_;

	friend class GameObject;
	friend class World;
};
//----------------------------------------------------------------------------//
} // end namespace he
//----------------------------------------------------------------------------//
#endif // HE_BEHAVIOR_H
