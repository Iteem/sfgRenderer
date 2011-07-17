#include <sfgRenderer/sfgRenderer.hpp>
#include <sfgRenderer/Spritebox.hpp>
#include <SFGUI/Window.hpp>
#include <SFGUI/Button.hpp>
#include <SFGUI/Label.hpp>
#include <SFML/Graphics/Shape.hpp>
#include <SFML/Graphics/Text.hpp>

namespace sfgr {

sfgRenderer::sfgRenderer() :
	Engine()
{
    // Set defaults.
	SetProperty<float>( "Window.Title.Height", 26.f );
	SetProperty<unsigned int>( "Window.Title.FontSize", 18 );
	SetProperty<sf::Color>( "Window.Title.BackgroundColor", sf::Color( 0x99, 0x99, 0x99 ) );
	SetProperty<sf::Color>( "Window.BackgroundColor", sf::Color( 0x88, 0x88, 0x88 ) );
	SetProperty<float>( "Window.BorderWidth", 2.f );
	SetProperty<sf::Color>( "Window.LightBorderColor", sf::Color( 0xCC, 0xCC, 0xCC ) );
	SetProperty<sf::Color>( "Window.DarkBorderColor", sf::Color( 0x55, 0x55, 0x55 ) );
	SetProperty<float>( "Window.ShadowDistance", 2.f );
	SetProperty<sf::Uint8>( "Window.ShadowAlpha", 100 );

	SetProperty<sf::Color>( "Button.Normal.LightBorderColor", sf::Color( 0xCC, 0xCC, 0xCC ) );
	SetProperty<sf::Color>( "Button.Normal.DarkBorderColor", sf::Color( 0x55, 0x55, 0x55 ) );
	SetProperty<sf::Color>( "Button.Normal.BackgroundColor", sf::Color( 0x99, 0x99, 0x99 ) );
	SetProperty<sf::Color>( "Button.Normal.TextColor", sf::Color( 0xFF, 0xFF, 0xFF ) );
	SetProperty<float>( "Button.Normal.BorderWidth", 1.f );
	SetProperty<sf::Color>( "Button.Prelight.BackgroundColor", sf::Color( 0xAA, 0xAA, 0xAA ) );
	SetProperty<sf::Color>( "Button.Prelight.TextColor", sf::Color( 0x00, 0x00, 0x00 ) );
	SetProperty<sf::Color>( "Button.Active.BackgroundColor", sf::Color( 0x77, 0x77, 0x77 ) );
	SetProperty<sf::Color>( "Button.Active.TextColor", sf::Color( 0x00, 0x00, 0x00 ) );
	SetProperty<sf::Color>( "Button.Active.LightBorderColor", sf::Color( 0x55, 0x55, 0x55 ) );
	SetProperty<sf::Color>( "Button.Active.DarkBorderColor", sf::Color( 0xCC, 0xCC, 0xCC ) );

	SetProperty<std::string>( "Label.Font", "data/discognate.ttf" );
	SetProperty<unsigned int>( "Label.FontSize", 14 );

	// Register property types.
	RegisterProperty( "Button.Normal.BackgroundColor", Color );
	RegisterProperty( "Window.Title.FontSize", UnsignedInteger );


	m_font.LoadFromFile(GetProperty<std::string>("Label.Font"));
}

sf::Drawable* sfgRenderer::CreateWindowDrawable( boost::shared_ptr<sfg::Window> window ) const {
	sfg::RenderQueue* queue( new sfg::RenderQueue );

	float title_size = GetProperty<float>("Window.Title.Height");
	unsigned int title_font_size = GetProperty<unsigned int>("Window.Title.FontSize");

    static sf::Image box;
	static bool loaded = false;
    if(!loaded){
        box.LoadFromFile("data/window.png");
        box.SetSmooth(false);
        loaded = true;
    }

	Spritebox *windowSpritebox(new Spritebox());
	windowSpritebox->SetImage(box);
	windowSpritebox->SetDimension(sf::Vector2i(window->GetAllocation().Width, window->GetAllocation().Height));
	queue->Add(windowSpritebox);




	if( !window->HasStyle( sfg::Window::Titlebar ) ) {
		title_size = 0;
	}

	if( title_size > 0 ) {
        sf::Text*  title_text(
			new sf::Text(
				window->GetTitle(),
				m_font,
				title_font_size
			)
		);

		// Calculate title text position.
		sf::Vector2f  title_position(
			std::floor( 7.5f + .5f ),
			std::floor( ((title_size / 2.f) - (static_cast<float>( title_font_size ) / 2.f)) + .5f )
		);

		title_text->SetPosition(title_position);
		title_text->SetColor(sf::Color(255, 255, 255));

		queue->Add(title_text);
	}

	return queue;
}

sf::Drawable* sfgRenderer::CreateButtonDrawable( boost::shared_ptr<sfg::Button> button ) const {
    sfg::RenderQueue*  queue( new sfg::RenderQueue );

	static sf::Image box;
	static bool loaded = false;
    if(!loaded){
        box.LoadFromFile("data/box.png");
        loaded = true;
    }

	Spritebox *spritebox(new Spritebox());
	spritebox->SetImage(box);
	spritebox->SetDimension(sf::Vector2i(button->GetAllocation().Width, button->GetAllocation().Height));
	queue->Add(spritebox);

	return queue;
}

sf::Drawable* sfgRenderer::CreateLabelDrawable( boost::shared_ptr<sfg::Label> label ) const {
    sf::Text*  vis_label(new sf::Text(label->GetText(), m_font, GetProperty<unsigned int>("Label.FontSize")));

	// Calculate alignment.
	sf::Vector2f  avail_space( label->GetAllocation().Width - label->GetRequisition().x, label->GetAllocation().Height - label->GetRequisition().y );
	sf::Vector2f  position( avail_space.x * label->GetAlignment().x, avail_space.y * label->GetAlignment().y );

	vis_label->SetPosition( std::floor( position.x + .5f ), std::floor( position.y + .5f ) );

	sfg::RenderQueue*  queue( new sfg::RenderQueue );
	queue->Add( vis_label );

	return queue;
}

} //namespace sfgr
