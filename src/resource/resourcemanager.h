#ifndef HE_RESOURCEMANAGER_H
#define HE_RESOURCEMANAGER_H
//----------------------------------------------------------------------------//
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
//----------------------------------------------------------------------------//
#include "dllexport.h"
#include "core/assert.h"
#include "resource/resourcepack.h"
//----------------------------------------------------------------------------//
namespace he {
//----------------------------------------------------------------------------//
class ENGINE_API ResourceManager
{
public:
	ResourceManager() : defaultResPack_(0) {}

	void addResourcePack(const std::string &name);
	void removeResourcePack(const std::string &name);
	ResourcePack& getResourcePack(const std::string &name);

	// Sets the default Resource Pack
	// Every following call to 'getResource' will use this
	void setDefaultResourcePack(const std::string &name);
	ResourcePack& getDefaultResourcePack() const;

	ResourceData getResource(const std::string &name) const;
	std::string getTextResource(const std::string &name) const;

	sf::Texture& getTexture(const std::string &name);
	sf::Font& getFont(const std::string &name);
	sf::SoundBuffer& getSoundBuffer(const std::string &name);

private:
	typedef std::map<std::string, ResourcePack> ResourcePackMap;
	ResourcePackMap resPacks_;

	ResourcePack *defaultResPack_;

	typedef std::map<std::string, sf::Texture> Textures;
	Textures textures_;
	typedef std::map<std::string, sf::Font> Fonts;
	Fonts fonts_;
	typedef std::map<std::string, sf::SoundBuffer> SoundBuffers;
	SoundBuffers soundBuffers_;
};
//----------------------------------------------------------------------------//
inline ResourcePack& ResourceManager::getDefaultResourcePack() const
{
	Assert(defaultResPack_, "defaultResPack shouldn't be null");
	return *defaultResPack_;
}
//----------------------------------------------------------------------------//
inline ResourceData ResourceManager::getResource(const std::string &name) const
{
	Assert(defaultResPack_, "defaultResPack shouldn't be null");
	return defaultResPack_->getResource(name);
}
//----------------------------------------------------------------------------//
inline std::string ResourceManager::getTextResource(const std::string &name) const
{
	Assert(defaultResPack_, "defaultResPack shouldn't be null");
	return defaultResPack_->getTextResource(name);
}
//----------------------------------------------------------------------------//
} // end namespace he
//----------------------------------------------------------------------------//
#endif // HE_RESOURCEMANAGER_H
