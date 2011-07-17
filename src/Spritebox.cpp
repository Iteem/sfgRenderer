#include <sfgRenderer/Spritebox.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

namespace sfgr {

Spritebox::Spritebox() :
m_subRect(0, 0, 1, 1),
m_dimension(0, 0)
{
}

void Spritebox::SetImage(const sf::Image &image, bool adjustSubRect)
{
	m_image = &image;
	if(adjustSubRect){
        m_subRect = sf::IntRect(0, 0, m_image->GetWidth(), m_image->GetHeight());
	}
}

const sf::Image *Spritebox::GetImage() const
{
    return m_image;
}

void Spritebox::SetSubRect(sf::IntRect subRect)
{
    m_subRect = subRect;
}

const sf::IntRect &Spritebox::GetSubRect() const
{
    return m_subRect;
}

void Spritebox::SetDimension(const sf::Vector2i &vec)
{
    m_dimension = vec;
}

const sf::Vector2i &Spritebox::GetDimension() const
{
    return m_dimension;
}

void Spritebox::Render(sf::RenderTarget& target, sf::Renderer& renderer) const
{
    if(m_dimension.x < 1 or m_dimension.y < 1)
        return;

    //round for pixel perfect rendering
    sf::Vector2f step(std::floor(static_cast<float>(m_image->GetWidth())/3.f + 0.5f),
                      std::floor(static_cast<float>(m_image->GetWidth())/3.f + 0.5f));

    sf::Vector2f coords[4];
    coords[0] = sf::Vector2f(0, 0);
    coords[1] = step;
    coords[2] = static_cast<sf::Vector2f>(m_dimension) - step;
    coords[3] = static_cast<sf::Vector2f>(m_dimension);

    renderer.SetTexture(m_image);

    for(unsigned int x = 0; x < 3; ++x){
        renderer.Begin(sf::Renderer::TriangleStrip);
        for(unsigned int y = 0; y < 4; ++y){
            renderer.AddVertex(coords[x].x,   coords[y].y,     x/3.f, y/3.f, sf::Color::White);
            renderer.AddVertex(coords[x+1].x, coords[y].y, (x+1)/3.f, y/3.f, sf::Color::White);
        }
        renderer.End();
    }
}

} //namespace sfgr
