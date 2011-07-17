#ifndef SFGRENDERER_HPP_INCLUDED
#define SFGRENDERER_HPP_INCLUDED

#include <sfgRenderer/Config.hpp>
#include <SFGUI/Engine.hpp>
#include <SFGUI/RenderQueue.hpp>

namespace sfgr {

/** sfgRenderer
 */
class SFGRENDERER_API sfgRenderer : public sfg::Engine {
	public:
		sfgRenderer();

		sf::Drawable* CreateWindowDrawable( boost::shared_ptr<sfg::Window> window ) const;
		sf::Drawable* CreateButtonDrawable( boost::shared_ptr<sfg::Button> button ) const;
		sf::Drawable* CreateLabelDrawable( boost::shared_ptr<sfg::Label> label ) const;

	private:
        sf::Font m_font;
};

} //namespace sfgr

#endif // SFGRENDERER_HPP_INCLUDED
