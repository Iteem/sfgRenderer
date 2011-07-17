#ifndef SPRITEBOX_HPP_INCLUDED
#define SPRITEBOX_HPP_INCLUDED

#include <sfgRenderer/Config.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/System/Resource.hpp>

namespace sf {
	class Image;
	class RenderTarget;
}

namespace sfgr {

/** The spritebox class renders scalable boxes.
 * A box consists of 9 graphics: 4 corners, 4 sides and the center.
 */
class SFGRENDERER_API Spritebox : public sf::Drawable{
	public:
		Spritebox();

		void SetImage(const sf::Image &image, bool adjustSubRect = true);

		const sf::Image *GetImage() const;

		void SetSubRect(sf::IntRect subRect);

		const sf::IntRect &GetSubRect() const;

		void SetDimension(const sf::Vector2i &vec);

		const sf::Vector2i &GetDimension() const;

	private:
        virtual void Render(sf::RenderTarget& target, sf::Renderer& renderer) const;

		sf::IntRect   m_subRect;
		sf::Vector2i  m_dimension;

		sf::ResourcePtr<sf::Image> m_image;
};

}

#endif // SPRITEBOX_HPP_INCLUDED
