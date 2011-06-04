#ifndef CONFIG_HPP_INCLUDED
#define CONFIG_HPP_INCLUDED

#if defined( _WIN32 ) || defined( __WIN32__ )
	#if !defined( SFGRENDERER_STATIC )
		#if defined( SFGRENDERER_EXPORT )
			#define SFGRENDERER_API __declspec( dllexport )
		#else
			#define SFGRENDERER_API __declspec( dllimport )
		#endif
	#else
		#define SFGRENDERER_API
	#endif
#else
	#define SFGRENDERER_API
#endif

#endif // CONFIG_HPP_INCLUDED
