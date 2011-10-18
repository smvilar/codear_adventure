#ifndef HE_SFMLVIEW_H
#define HE_SFMLVIEW_H
//----------------------------------------------------------------------------//
#include "DllExport.h"
#include "core/View.h"
//----------------------------------------------------------------------------//
namespace sf
{
class Drawable;
}
//----------------------------------------------------------------------------//
namespace he {
//----------------------------------------------------------------------------//
class ENGINE_API SFMLView : public View
{
public:
	SFMLView(sf::Drawable *pDrawable);

	virtual void update(u32 elapsedMs);
	virtual void render(Renderer& renderer);

private:
	sf::Drawable *_drawable;
};
//----------------------------------------------------------------------------//
} // end namespace he
//----------------------------------------------------------------------------//
#endif // HE_SFMLVIEW_H
