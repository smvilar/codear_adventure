#include "behaviors/SpriteBehavior.h"
//----------------------------------------------------------------------------//
#include <string>
//----------------------------------------------------------------------------//
#include "gameobject/goworld.h"
#include "gameobject/gameobject.h"
#include "gameobject/goattribute.h"
#include "resource/ResourceManager.h"
#include "video/Texture.h"
#include "core/Scene.h"
//----------------------------------------------------------------------------//
using namespace foragers;
//----------------------------------------------------------------------------//
GOBehavior* SpriteBehavior::clone() const
{
	return dynamic_cast<GOBehavior*>(new SpriteBehavior());
}
//----------------------------------------------------------------------------//
void SpriteBehavior::added()
{
	using std::string;

	GOAttribute *attr = _pOwner->getAttribute("sprite_filename");
	const string &filename = attr->getValue<string>();
	
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
