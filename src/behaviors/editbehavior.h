#ifndef HE_EDITBEHAVIOR_H
#define HE_EDITBEHAVIOR_H
//----------------------------------------------------------------------------//
#include <vector>
//----------------------------------------------------------------------------//
#include <SFML/Graphics.hpp>
//----------------------------------------------------------------------------//
#include "dllexport.h"
#include "core/types.h"
#include "gameobject/behavior.h"
//----------------------------------------------------------------------------//
namespace he {
//----------------------------------------------------------------------------//
class GameObject;
class MouseUtil;
//----------------------------------------------------------------------------//
class ENGINE_API EditBehavior : public Behavior
{
public:
	virtual void update();
	virtual Behavior* clone() const;

private:
	virtual void activate();
	virtual void deactivate();

private:
	enum Mode
	{
		INACTIVE,
		SELECT,
		DRAG
	};
	Mode mode_;

	typedef std::vector<GameObject*> GameObjectVector;
	GameObjectVector objects_;

	sf::Shape gizmo_;
	GameObject* activeObject_;

	bool tabPressed_;

	MouseUtil* mouseUtil_;

private:
	void updateSelect();
	void updateDrag();

	void initGizmo();
	void setGizmo(s32 x, s32 y, u32 w, u32 h);
};
//----------------------------------------------------------------------------//
} // end namespace he
//----------------------------------------------------------------------------//
#endif // HE_EDITBEHAVIOR_H
