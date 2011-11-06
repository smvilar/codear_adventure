#include "resource/resourcemanager.h"
//----------------------------------------------------------------------------//
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
//----------------------------------------------------------------------------//
using namespace he;
//----------------------------------------------------------------------------//
void ResourceManager::addResourcePack(const std::string &name)
{
	resPacks_[name].load(name);
	if (!defaultResPack_)
		defaultResPack_ = &resPacks_[name];
}
//----------------------------------------------------------------------------//
void ResourceManager::removeResourcePack(const std::string &name)
{
	Assert(resPacks_.find(name) != resPacks_.end(),
		   "ResourcePack not found");
	if (defaultResPack_ == &resPacks_[name])
		defaultResPack_ = 0;
	resPacks_.erase(name);
}
//----------------------------------------------------------------------------//
ResourcePack& ResourceManager::getResourcePack(const std::string &name)
{
	Assert(resPacks_.find(name) != resPacks_.end(),
		   "ResourcePack not found");
	return resPacks_[name];
}
//----------------------------------------------------------------------------//
void ResourceManager::setDefaultResourcePack(const std::string &name)
{
	Assert(resPacks_.find(name) != resPacks_.end(),
		   "ResourcePack not found");
	defaultResPack_ = &resPacks_[name];
}
//----------------------------------------------------------------------------//
sf::Texture& ResourceManager::getTexture(const std::string &name)
{
	Textures::iterator it = textures_.find(name);
	if (it == textures_.end())
	{
		// Load the texture
		ResourceData res = defaultResPack_->getResource(name);
		sf::Texture &texture = textures_[name];
		if (!texture.LoadFromMemory(res.data, res.size))
		{
			std::cerr << "Error loading texture: " << name << std::endl;
			Assert(false, "Error loading texture");
		}
	}
	return textures_[name];
}
//----------------------------------------------------------------------------//
sf::Font& ResourceManager::getFont(const std::string &name)
{
	Fonts::iterator it = fonts_.find(name);
	if (it == fonts_.end())
	{
		// Load the font
		std::cout << "Loading font " << name << std::endl;
		ResourceData res = defaultResPack_->getResource(name);
		sf::Font &font = fonts_[name];
		if (!font.LoadFromMemory(res.data, res.size))
		{
			std::cerr << "Error loading font: " << name << std::endl;
			Assert(false, "Error loading font");
		}
	}
	return fonts_[name];
}
//----------------------------------------------------------------------------//
sf::SoundBuffer& ResourceManager::getSoundBuffer(const std::string &name)
{
	SoundBuffers::iterator it = soundBuffers_.find(name);
	if (it == soundBuffers_.end())
	{
		// Load the sound buffer
		ResourceData res = defaultResPack_->getResource(name);
		sf::SoundBuffer &soundBuffer = soundBuffers_[name];
		if (!soundBuffer.LoadFromMemory(res.data, res.size))
		{
			std::cerr << "Error loading sound buffer: " << name << std::endl;
			Assert(false, "Error loading sound buffer");
		}
	}
	return soundBuffers_[name];
}
//----------------------------------------------------------------------------//
