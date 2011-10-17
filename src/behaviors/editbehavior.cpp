#include "behaviors/editbehavior.h"
//----------------------------------------------------------------------------//
#include "math/Rect.h"
#include "gameobject/gameobject.h"
#include "gameobject/world.h"
//----------------------------------------------------------------------------//
using namespace he;
//----------------------------------------------------------------------------//
Behavior* EditBehavior::clone() const
{
	return new EditBehavior;
}
//----------------------------------------------------------------------------//
void EditBehavior::activate()
{
	_mode = SELECT;
	_objects = _pOwner->getAttributeAs<GameObjectVector>("objects");
	_window = _pWorld->getObject("Game")->getAttributeAs<sf::Window*>("window");
}
//----------------------------------------------------------------------------//
void EditBehavior::update()
{
	switch (_mode)
	{
	case SELECT:
		updateSelect();
		break;
	case DRAG:
		updateDrag();
		break;
	}
}
//----------------------------------------------------------------------------//
void EditBehavior::updateSelect()
{
	const sf::Vector2i& mousePos = sf::Mouse::GetPosition(*_window);

	//check the topmost object that collides with the mouse
	GameObjectVector::reverse_iterator it = _objects.rbegin();
	for (; it != _objects.rend(); ++it)
	{
		GameObject* object = *it;

		int posX = object->getAttributeAs<int>("pos_x");
		int posY = object->getAttributeAs<int>("pos_y");
		int width = object->getAttributeAs<float>("width");
		int height = object->getAttributeAs<float>("height");

		Recti rect(posX, posY, width, height);
		if (rect.contains(Vector2i(mousePos.x, mousePos.y)))
		{
			//std::cout << "Over object: " << object->name << std::endl;
			if (sf::Mouse::IsButtonPressed(sf::Mouse::Left))
			{
				_mode = DRAG;
				_activeObject = object;
				_lastMousePos = mousePos;
			}
			break;
		}
	}
}
//----------------------------------------------------------------------------//
void EditBehavior::updateDrag()
{
	const sf::Vector2i& mousePos = sf::Mouse::GetPosition(*_window);
	sf::Vector2i movement = mousePos - _lastMousePos;

	Attribute *aPosX = _activeObject->getAttribute("pos_x");
	Attribute *aPosY = _activeObject->getAttribute("pos_y");
	aPosX->setValue(aPosX->getValue<int>()+movement.x);
	aPosY->setValue(aPosY->getValue<int>()+movement.y);

	_lastMousePos = mousePos;

	if (!sf::Mouse::IsButtonPressed(sf::Mouse::Left))
	{
		_mode = SELECT;
		_activeObject = 0;
	}
}
//----------------------------------------------------------------------------//
