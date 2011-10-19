#include "behaviors/SpriteBehavior.h"
//----------------------------------------------------------------------------//
#include <string>
//----------------------------------------------------------------------------//
#include "gameobject/world.h"
#include "gameobject/gameobject.h"
#include "gameobject/attribute.h"
#include "core/Scene.h"
//----------------------------------------------------------------------------//
using namespace he;
//----------------------------------------------------------------------------//
Behavior* SpriteBehavior::clone() const
{
	return new SpriteBehavior;
}
//----------------------------------------------------------------------------//
void SpriteBehavior::added()
{
	using std::string;

	const string &filename = _pOwner->getAttributeAs<string>("sprite_filename");
	int framesHorizontal = 1;
	int framesVertical = 1;
	int msPerFrame = 0;

	Attribute* framesHorizAttr = _pOwner->getAttribute("frames_horizontal");
	if (framesHorizAttr)
		framesHorizontal = framesHorizAttr->getValue<int>();
	Attribute* framesVerticAttr = _pOwner->getAttribute("frames_vertical");
	if (framesVerticAttr)
		framesVertical = framesVerticAttr->getValue<int>();
	Attribute* msPerFrameAttr = _pOwner->getAttribute("ms_per_frame");
	if (msPerFrameAttr)
		msPerFrame = msPerFrameAttr->getValue<int>();
	
	//ResourceManager &resMgr = _pWorld->getResourceManager();
	//TexturePtr texture = resMgr.get<Texture>(filename.c_str());
	//_sprite = Sprite(texture, framesHorizontal, framesVertical, msPerFrame);
	sf::Texture texture;
	if (!texture.LoadFromFile(filename))
		std::cerr << "Error loading sprite: " << filename << std::endl;
	//_sprite = sf::Sprite(texture);
	_sprite.SetTexture(texture);

	_posX = _pOwner->getAttribute("pos_x");
	_posY = _pOwner->getAttribute("pos_y");
	_rotation = _pOwner->getAttribute("rotation");
	_scale = _pOwner->getAttribute("scale");

	Attribute* width = _pOwner->getAttribute("width");
	Attribute* height = _pOwner->getAttribute("height");
	if (!width)
		_pOwner->addAttribute("width", new Attribute(_sprite.GetSize().x));
	if (!height)
		_pOwner->addAttribute("height", new Attribute(_sprite.GetSize().y));
}
//----------------------------------------------------------------------------//
void SpriteBehavior::removed()
{
	// clean texture?
}
//----------------------------------------------------------------------------//
void SpriteBehavior::activate()
{
	_pWorld->getScene().addDrawable(&_sprite);
}
//----------------------------------------------------------------------------//
void SpriteBehavior::deactivate()
{
	_pWorld->getScene().removeDrawable(&_sprite);
}
//----------------------------------------------------------------------------//
void SpriteBehavior::update()
{
	_sprite.SetPosition(_posX->getValue<int>(), _posY->getValue<int>());
}
//----------------------------------------------------------------------------//
