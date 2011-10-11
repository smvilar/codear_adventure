#include "behaviors/SpriteBehavior.h"
//----------------------------------------------------------------------------//
#include <string>
//----------------------------------------------------------------------------//
#include "gameobject/world.h"
#include "gameobject/gameobject.h"
#include "gameobject/attribute.h"
#include "resource/ResourceManager.h"
#include "video/Texture.h"
#include "core/Scene.h"
//----------------------------------------------------------------------------//
using namespace foragers;
//----------------------------------------------------------------------------//
Behavior* SpriteBehavior::clone() const
{
	return dynamic_cast<Behavior*>(new SpriteBehavior());
}
//----------------------------------------------------------------------------//
void SpriteBehavior::added()
{
	using std::string;

	const string &filename = _pOwner->getAttributeAs<string>("sprite_filename");
	
	ResourceManager &resMgr = _pWorld->getResourceManager();
	TexturePtr texture = resMgr.get<Texture>(filename.c_str());
	_sprite = Sprite(texture, 6, 1, 120);

	_posX = _pOwner->getAttribute("pos_x");
	_posY = _pOwner->getAttribute("pos_y");
	_rotation = _pOwner->getAttribute("rotation");
	_scale = _pOwner->getAttribute("scale");
}
//----------------------------------------------------------------------------//
void SpriteBehavior::removed()
{
	// clean texture?
}
//----------------------------------------------------------------------------//
void SpriteBehavior::activate()
{
	_pWorld->getScene().addEntity(&_sprite);
}
//----------------------------------------------------------------------------//
void SpriteBehavior::deactivate()
{
	_pWorld->getScene().removeEntity(&_sprite);
}
//----------------------------------------------------------------------------//
void SpriteBehavior::update()
{
	float posX, posY;
	posX = (float)_posX->getValue<int>();
	posY = (float)_posY->getValue<int>();
	_sprite.setPosition(Vector2f(posX, posY));
	
	if (_rotation)
		_sprite.setAngle((float)_rotation->getValue<int>());
	if (_scale)
		_sprite.setScale(Vector2f((float)_scale->getValue<int>()));
}
//----------------------------------------------------------------------------//
