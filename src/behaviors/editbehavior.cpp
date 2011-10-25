#include "behaviors/editbehavior.h"
//----------------------------------------------------------------------------//
#include "math/Rect.h"
#include "gameobject/gameobject.h"
#include "gameobject/world.h"
//----------------------------------------------------------------------------//
using namespace he;
//----------------------------------------------------------------------------//
void EditBehavior::activate()
{
	mode_ = SELECT;
	objects_ = pOwner_->getAttributeAs<GameObjectVector>("objects");
	window_ = pWorld_->getObject("Game")->getAttributeAs<sf::RenderWindow*>("window");

	initGizmo();
	setGizmo(-10, -10, 0, 0);
	pWorld_->getScene().addDrawable(&gizmo_);

	mode_ = INACTIVE;
	tabPressed_ = false;
}
//----------------------------------------------------------------------------//
void EditBehavior::deactivate()
{
	pWorld_->getScene().removeDrawable(&gizmo_);
}
//----------------------------------------------------------------------------//
void EditBehavior::update()
{
	if (!tabPressed_ && sf::Keyboard::IsKeyPressed(sf::Keyboard::Tab))
	{
		mode_ = (mode_ == INACTIVE) ? SELECT : INACTIVE;
		tabPressed_ = true;
	}
	else if (!sf::Keyboard::IsKeyPressed(sf::Keyboard::Tab))
	{
		tabPressed_ = false;
	}

	switch (mode_)
	{
	case SELECT:
		updateSelect();
		break;
	case DRAG:
		updateDrag();
		break;
	case INACTIVE:
		setGizmo(-1, -1, 0, 0);
		break;
	}
}
//----------------------------------------------------------------------------//
Behavior* EditBehavior::clone() const
{
	return new EditBehavior;
}
//----------------------------------------------------------------------------//
void EditBehavior::updateSelect()
{
	const sf::Vector2i &mousePos = sf::Mouse::GetPosition(*window_);

	setGizmo(-10, -10, 0, 0);
	//check the topmost object that collides with the mouse
	GameObjectVector::reverse_iterator it = objects_.rbegin();
	for (; it != objects_.rend(); ++it)
	{
		GameObject* object = *it;

		int posX = object->getAttributeAs<int>("x");
		int posY = object->getAttributeAs<int>("y");
		int width = object->getAttributeAs<int>("width");
		int height = object->getAttributeAs<int>("height");

		Recti rect(posX, posY, width, height);
		if (rect.contains(Vector2i(mousePos.x, mousePos.y)))
		{
			setGizmo(posX, posY, width, height);
			if (sf::Mouse::IsButtonPressed(sf::Mouse::Left))
			{
				mode_ = DRAG;
				activeObject_ = object;
				lastMousePos_ = mousePos;
			}
			break;
		}
	}
}
//----------------------------------------------------------------------------//
void EditBehavior::updateDrag()
{
	const sf::Vector2i& mousePos = sf::Mouse::GetPosition(*window_);
	sf::Vector2i movement = mousePos - lastMousePos_;

	Attribute *posXAttr = activeObject_->getAttribute("x");
	Attribute *posYAttr = activeObject_->getAttribute("y");
	int posX = posXAttr->getValue<int>() + movement.x;
	int posY = posYAttr->getValue<int>() + movement.y;
	posXAttr->setValue(posX);
	posYAttr->setValue(posY);

	gizmo_.SetPosition(posX, posY);

	lastMousePos_ = mousePos;

	if (!sf::Mouse::IsButtonPressed(sf::Mouse::Left))
	{
		mode_ = SELECT;
		activeObject_ = 0;
	}
}
//----------------------------------------------------------------------------//
void EditBehavior::initGizmo()
{
	sf::Color outlineColor(255, 0, 0);
	sf::Color color(255, 255, 255, 50);
	gizmo_.AddPoint(0, 0, color, outlineColor);
	gizmo_.AddPoint(1, 0, color, outlineColor);
	gizmo_.AddPoint(1, 1, color, outlineColor);
	gizmo_.AddPoint(0, 1, color, outlineColor);
	gizmo_.EnableOutline(true);
	gizmo_.SetOutlineThickness(2);
}
//----------------------------------------------------------------------------//
void EditBehavior::setGizmo(s32 x, s32 y, u32 w, u32 h)
{
	gizmo_.SetPointPosition(0, 0, 0);
	gizmo_.SetPointPosition(1, w, 0);
	gizmo_.SetPointPosition(2, w, h);
	gizmo_.SetPointPosition(3, 0, h);
	gizmo_.SetPosition(x, y);
}
//----------------------------------------------------------------------------//
