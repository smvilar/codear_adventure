#ifndef FORAGERS_TEXT_H
#define FORAGERS_TEXT_H
//----------------------------------------------------------------------------//
#include "DllExport.h"
#include "core/Entity.h"
#include "resource/Font.h"
#include "video/Texture.h"
//----------------------------------------------------------------------------//
namespace foragers
{
//----------------------------------------------------------------------------//
class Renderer;
class ResourceManager;
//----------------------------------------------------------------------------//
class ENGINE_API Text
	: public Entity
{
public:
	Text();
	~Text();

	void load(ResourceManager& resManager, const char* filename);

	virtual void update(u32 elapsedMs);
	virtual void render(Renderer& renderer);

    virtual const Vector2f& getSize() const;

	void setText(const char* text, u32 fontSize);

/// Font
public:
	FontPtr getFont();

private:
	FontPtr _font;

/// Texture
public:
	TexturePtr getTexture() const;

private:
	TexturePtr _texture;
	static u32 s_textureCount;
};
//----------------------------------------------------------------------------//
} // end namespace foragers
//----------------------------------------------------------------------------//
#endif // FORAGERS_TEXT_H