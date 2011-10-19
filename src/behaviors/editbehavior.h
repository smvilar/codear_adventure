#ifndef HE_EDITBEHAVIOR_H
#define HE_EDITBEHAVIOR_H
//----------------------------------------------------------------------------//
#include <vector>
//----------------------------------------------------------------------------//
#include <SFML/Graphics.hpp>
//----------------------------------------------------------------------------//
#include "DllExport.h"
#include "gameobject/behavior.h"
//----------------------------------------------------------------------------//
namespace he {
//----------------------------------------------------------------------------//
class GameObject;
//----------------------------------------------------------------------------//
class ENGINE_API EditBehavior : public Behavior
{
public:
	virtual void update();
	virtual Behavior* clone() const;

private:
	virtual void activate();

private:
	enum Mode
	{
		SELECT,
		DRAG
	};
	Mode _mode;

	typedef std::vector<GameObject*> GameObjectVector;
	GameObjectVector _objects;
	sf::RenderWindow* _window;

	GameObject* _activeObject;
	sf::Vector2i _lastMousePos;

private:
	void updateSelect();
	void updateDrag();
};
//----------------------------------------------------------------------------//
} // end namespace he
//----------------------------------------------------------------------------//
#endif // HE_EDITBEHAVIOR_H
