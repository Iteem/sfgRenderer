#include <sfgRenderer/sfgRenderer.hpp>
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
	SetProperty<float>( "Window.Title.Height", 20.f );
	SetProperty<unsigned int>( "Window.Title.FontSize", 14 );
	SetProperty<sf::Color>( "Window.Title.BackgroundColor", sf::Color( 0x99, 0x99, 0x99 ) );
	SetProperty<sf::Color>( "Window.BackgroundColor", sf::Color( 0x7f, 0xff, 0x00 ) );
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

	SetProperty<std::string>( "Label.Font", "" );
	SetProperty<unsigned int>( "Label.FontSize", 12 );

	// Register property types.
	RegisterProperty( "Button.Normal.BackgroundColor", Color );
	RegisterProperty( "Window.Title.FontSize", UnsignedInteger );
}

sf::Drawable* sfgRenderer::CreateWindowDrawable( boost::shared_ptr<sfg::Window> window ) const {
	sfg::RenderQueue* queue( new sfg::RenderQueue );
	sf::Color background_color( GetProperty<sf::Color>( "Window.BackgroundColor", window ) );
	sf::Color border_color_light( GetProperty<sf::Color>( "Window.LightBorderColor", window ) );
	sf::Color border_color_dark( GetProperty<sf::Color>( "Window.DarkBorderColor", window ) );
	sf::Color title_background_color( GetProperty<sf::Color>( "Window.Title.BackgroundColor", window ) );
	float border_width( GetProperty<float>( "Window.BorderWidth", window ) );
	float title_size( GetProperty<float>( "Window.Title.Height", window ) );
	float shadow_distance( GetProperty<float>( "Window.ShadowDistance", window ) );
	sf::Uint8 shadow_alpha( GetProperty<sf::Uint8>( "Window.ShadowAlpha", window ) );
	unsigned int title_font_size( GetProperty<unsigned int>( "Window.Title.FontSize", window ) );

	if( window->HasStyle( sfg::Window::Background ) ) {
		// Shadow.
		if( shadow_distance > 0.f ) {
			sf::Color  shadow_color( 0, 0, 0, shadow_alpha );

			queue->Add( new sf::Shape( sf::Shape::Rectangle( window->GetAllocation().Width + .1f, shadow_distance + .1f, shadow_distance, window->GetAllocation().Height - shadow_distance, shadow_color ) ) ); // Right.
			queue->Add( new sf::Shape( sf::Shape::Rectangle( shadow_distance + .1f, window->GetAllocation().Height + .1f, window->GetAllocation().Width, shadow_distance, shadow_color ) ) ); // Bottom.
		}

		if( border_width > 0 ) {
			queue->Add( CreateBorder( window->GetAllocation(), border_width, border_color_light, border_color_dark ) );
		}

		sf::Shape*  background(
			new sf::Shape(
				sf::Shape::Rectangle(
					border_width + .1f,
					border_width + .1f,
					window->GetAllocation().Width - 2 * border_width,
					window->GetAllocation().Height - 2 * border_width,
					background_color
				)
			)
		);

		queue->Add( background );
	}

	if( !window->HasStyle( sfg::Window::Titlebar ) ) {
		title_size = 0;
	}

	if( title_size > 0 ) {
		sf::Shape*  title(
			new sf::Shape(
				sf::Shape::Rectangle(
					border_width + .1f,
					border_width + .1f,
					window->GetAllocation().Width - 2 * border_width,
					title_size,
					title_background_color
				)
			)
		);

		sf::Text*  title_text(
			new sf::Text(
				window->GetTitle(),
				sf::Font::GetDefaultFont(),
				title_font_size
			)
		);

		// Calculate title text position.
		sf::Vector2f  title_position(
			std::floor( border_width + 5.f + .5f ),
			std::floor( border_width + ((title_size / 2.f) - (static_cast<float>( title_font_size ) / 2.f)) + .5f )
		);

		title_text->SetPosition( title_position );
		title_text->SetColor( sf::Color( 0, 0, 0 ) );

		queue->Add( title );
		queue->Add( title_text );
	}


	return queue;
}

sfg::RenderQueue* sfgRenderer::CreateBorder( const sf::FloatRect& rect, float border_width, const sf::Color& light_color, const sf::Color& dark_color ) {
	sfg::RenderQueue* queue( new sfg::RenderQueue );

	queue->Add( new sf::Shape( sf::Shape::Rectangle( rect.Width - border_width + .1f, .1f, border_width, rect.Height, dark_color ) ) ); // Right.
	queue->Add( new sf::Shape( sf::Shape::Rectangle( .1f, rect.Height - border_width + .1f, rect.Width, border_width, dark_color ) ) ); // Bottom.

	for( float delta = 0.f; delta < border_width; delta += 1.f ) {
		queue->Add( new sf::Shape( sf::Shape::Line( .1f, delta + .1f, rect.Width - delta, delta, 1.f, light_color ) ) ); // Top.
		queue->Add( new sf::Shape( sf::Shape::Line( delta + .1f, .1f, delta, rect.Height - delta, 1.f, light_color ) ) ); // Left.
	}

	return queue;
}

sf::Drawable* sfgRenderer::CreateButtonDrawable( boost::shared_ptr<sfg::Button> button ) const {
	sf::Color border_color_light( GetProperty<sf::Color>( "Button.Normal.LightBorderColor", button ) );
	sf::Color border_color_dark( GetProperty<sf::Color>( "Button.Normal.DarkBorderColor", button ) );
	sf::Color background_color( GetProperty<sf::Color>( "Button.Normal.BackgroundColor", button ) );
	sf::Color text_color( GetProperty<sf::Color>( "Button.Normal.TextColor", button ) );
	float border_width( GetProperty<float>( "Button.Normal.BorderWidth", button ) );

	if( button->GetState() == sfg::Widget::Prelight ) {
		background_color = GetProperty<sf::Color>( "Button.Prelight.BackgroundColor", button );
		text_color = GetProperty<sf::Color>( "Button.Prelight.TextColor", button );
	}
	else if( button->GetState() == sfg::Widget::Active ) {
		background_color = GetProperty<sf::Color>( "Button.Active.BackgroundColor", button );
		text_color = GetProperty<sf::Color>( "Button.Active.TextColor", button );
		border_color_light = GetProperty<sf::Color>( "Button.Active.LightBorderColor", button );
		border_color_dark = GetProperty<sf::Color>( "Button.Active.DarkBorderColor", button );
	}

	sfg::RenderQueue*  queue( new sfg::RenderQueue );

	queue->Add(
		new sf::Shape(
			sf::Shape::Rectangle(
				0.f,
				0.f,
				button->GetAllocation().Width,
				button->GetAllocation().Height,
				background_color
			)
		)
	);

	queue->Add( CreateBorder( button->GetAllocation(), border_width, border_color_light, border_color_dark ) );

	return queue;
}

sf::Drawable* sfgRenderer::CreateLabelDrawable( boost::shared_ptr<sfg::Label> label ) const {
	const sf::Font&  font( LoadFontFromFile( GetProperty<std::string>( "Label.Font", label ) ) );
	const unsigned int&  font_size( GetProperty<unsigned int>( "Label.FontSize", label ) );

	sf::Text*  vis_label( new sf::Text( label->GetText(), font, font_size ) );

	// Calculate alignment.
	sf::Vector2f  avail_space( label->GetAllocation().Width - label->GetRequisition().x, label->GetAllocation().Height - label->GetRequisition().y );
	sf::Vector2f  position( avail_space.x * label->GetAlignment().x, avail_space.y * label->GetAlignment().y );

	vis_label->SetPosition( std::floor( position.x + .5f ), std::floor( position.y + .5f ) );

	sfg::RenderQueue*  queue( new sfg::RenderQueue );
	queue->Add( vis_label );

	return queue;
}

} //namespace sfgr
