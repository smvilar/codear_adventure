#include "video/animatedsprite.h"
//----------------------------------------------------------------------------//
#include <fstream>
//----------------------------------------------------------------------------//
#include "json/json.h"
#include "resource/resourcepack.h"
//----------------------------------------------------------------------------//
using namespace he;
//----------------------------------------------------------------------------//
bool AnimatedSprite::parse(const std::string &filename, ResourcePack &resPack)
{
	std::string text = resPack.getTextResource(filename);
	Json::Reader reader;
	Json::Value root;

	if (!reader.parse(text, root))
	{
		std::cerr << "Error parsing AnimatedSprite: "
				  << reader.getFormatedErrorMessages() << std::endl;
		return false;
	}

	const std::string &textureFilename = root["textureFilename"].asString();
	ResourceData res = resPack.getResource(textureFilename);

	if (!texture_.LoadFromMemory(res.data, res.size))
		std::cerr << "Error loading texture: " << textureFilename << std::endl;
	sprite_.SetTexture(texture_);

	u32 framesHorizontal = root["framesHorizontal"].asInt();
	u32 framesVertical = root["framesVertical"].asInt();
	if (framesHorizontal == 0) framesHorizontal = 1;
	if (framesVertical == 0) framesVertical = 1;
	Json::Value &animsArray = root["animations"];
	for (size_t i = 0; i < animsArray.size(); ++i)
		parseAnimation(animsArray[i], framesHorizontal, framesVertical);

	play(root["defaultAnimation"].asString());

	return true;
}
//----------------------------------------------------------------------------//
void AnimatedSprite::parseAnimation(Json::Value &root, u32 framesHoriz, u32 framesVert)
{
	const std::string &animName = root["name"].asString();
	u32 msPerFrame = root["msPerFrame"].asInt();
	u32 firstFrame = root["firstFrame"].asInt();
	u32 lastFrame = root["lastFrame"].asInt();
	u32 loopCount = root["loopCount"].asInt();
	u32 loopFromFrame = root["loopFromFrame"].asInt();

	animations_[animName] = SpriteAnimation(sprite_, framesHoriz, framesVert,
											msPerFrame, firstFrame, lastFrame,
											loopCount, loopFromFrame);
}
//----------------------------------------------------------------------------//
void AnimatedSprite::update(u32 elapsedMs)
{
	if (currentAnimation_)
		currentAnimation_->update(elapsedMs);
}
//----------------------------------------------------------------------------//
void AnimatedSprite::play(const std::string &animation)
{
	Animations::iterator it = animations_.find(animation);
	if (it != animations_.end())
		currentAnimation_ = &animations_[animation];
}
//----------------------------------------------------------------------------//
