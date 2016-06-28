#ifndef ___LMP3D_StringUtils_H___
#define ___LMP3D_StringUtils_H___

#include <string>

namespace LMP3D
{
	void replace( std::string & text, std::string const & toReplace, std::string const & replacement );
	std::string & trimLeft( std::string & text );
	std::string & trimRight( std::string & text );
	std::string lowerCase( std::string const & text );
	std::string upperCase( std::string const & text );

	inline void replace( std::string & text, char toReplace, char replacement )
	{
		char find[2] = { toReplace, '\0' };
		char replaced[2] = { replacement, '\0' };
		replace( text, find, replaced );
	}

	inline void replace( std::string & text, std::string const & toReplace, char replacement )
	{
		char replaced[2] = { replacement, '\0' };
		replace( text, toReplace, replaced );
	}

	inline void replace( std::string & text, char toReplace, std::string const & replacement )
	{
		char find[2] = { toReplace, '\0' };
		replace( text, find, replacement );
	}

	inline std::string & trim( std::string & text )
	{
		return trimLeft( trimRight( text ) );
	}
}

#endif
