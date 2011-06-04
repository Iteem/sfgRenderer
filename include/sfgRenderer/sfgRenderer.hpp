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
		/** Ctor.
		 */
		sfgRenderer();

		sf::Drawable* CreateWindowDrawable( boost::shared_ptr<sfg::Window> window ) const;
		sf::Drawable* CreateButtonDrawable( boost::shared_ptr<sfg::Button> button ) const;
		sf::Drawable* CreateLabelDrawable( boost::shared_ptr<sfg::Label> label ) const;

		/** Utility function to create borders.
		 * @param rect Rectangle.
		 * @param border_width Border width.
		 * @param light_color Color of lightened edges.
		 * @param dark_color Color of darkened edges.
		 * @return RenderQueue containing border (unmanaged memory!).
		 */
		static sfg::RenderQueue* CreateBorder( const sf::FloatRect& rect, float border_width, const sf::Color& light_color, const sf::Color& dark_color );

	private:
};

} //namespace sfgr

#endif // SFGRENDERER_HPP_INCLUDED
