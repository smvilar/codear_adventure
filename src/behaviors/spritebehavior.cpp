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

	if (!texture_.LoadFromFile(filename))
		std::cerr << "Error loading sprite: " << filename << std::endl;
	sprite_.SetTexture(texture_);

	spriteAnimation_.set(sprite_, framesHorizontal, framesVertical, msPerFrame);

	posX_ = _pOwner->getAttribute("pos_x");
	posY_ = _pOwner->getAttribute("pos_y");
	rotation_ = _pOwner->getAttribute("rotation");
	scale_ = _pOwner->getAttribute("scale");

	if (!_pOwner->getAttribute("width"))
		_pOwner->addAttribute("width", new Attribute(sprite_.GetSize().x));
	if (!_pOwner->getAttribute("height"))
		_pOwner->addAttribute("height", new Attribute(sprite_.GetSize().y));
}
//----------------------------------------------------------------------------//
void SpriteBehavior::removed()
{
	// clean texture?
}
//----------------------------------------------------------------------------//
void SpriteBehavior::activate()
{
	_pWorld->getScene().addDrawable(&sprite_);
}
//----------------------------------------------------------------------------//
void SpriteBehavior::deactivate()
{
	_pWorld->getScene().removeDrawable(&sprite_);
}
//----------------------------------------------------------------------------//
void SpriteBehavior::update()
{
	sprite_.SetPosition(posX_->getValue<int>(), posY_->getValue<int>());
	if (scale_)
		sprite_.SetScale(scale_->getValue<int>(), scale_->getValue<int>());

	// TODO: unhardcode
	spriteAnimation_.update(30);
}
//----------------------------------------------------------------------------//
