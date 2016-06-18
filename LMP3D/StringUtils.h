#ifndef ___LMP3D_StringUtils_H___
#define ___LMP3D_StringUtils_H___

#include <string>

namespace LMP3D
{
#if defined( _WIN32 )

	static char const PATH_SEPARATOR = '\\';

#else

	static char const PATH_SEPARATOR = '/';

#endif

	void replace( std::string & text, char toReplace, char replacement );
	void replace( std::string & text, std::string const & toReplace, char replacement );
	void replace( std::string & text, char toReplace, std::string const & replacement );
	void replace( std::string & text, std::string const & toReplace, std::string const & replacement );
	void trim_left( std::string & text );
	void trim_right( std::string & text );
	void trim( std::string & text );
	std::string getPath( std::string const & filePath );
	std::string getFileName( std::string const & filePath, bool withExtension = false );
}

#endif
