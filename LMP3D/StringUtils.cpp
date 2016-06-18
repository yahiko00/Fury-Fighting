#include "StringUtils.h"

namespace LMP3D
{
	void replace( std::string & text, char toReplace, char replacement )
	{
		char find[2] = { toReplace, '\0' };
		char replaced[2] = { replacement, '\0' };
		replace( text, find, replaced );
	}

	void replace( std::string & text, std::string const & toReplace, char replacement )
	{
		char replaced[2] = { replacement, '\0' };
		replace( text, toReplace, replaced );
	}

	void replace( std::string & text, char toReplace, std::string const & replacement )
	{
		char find[2] = { toReplace, '\0' };
		replace( text, find, replacement );
	}

	void replace( std::string & text, std::string const & toReplace, std::string const & replacement )
	{
		std::string temp;
		std::string ret;
		std::size_t currentPos = 0;
		std::size_t pos = 0;

		while ( ( pos = text.find( toReplace, currentPos ) ) != std::string::npos )
		{
			ret.append( text.substr( currentPos, pos - currentPos ) );
			ret.append( replacement );
			currentPos = pos + toReplace.size();
		}

		if ( currentPos != text.size() )
		{
			ret.append( text.substr( currentPos, pos - currentPos ) );
		}

		text = ret;
	}

	void trim_left( std::string & text )
	{
		size_t index = text.find_first_not_of( " \t" );

		if ( index != std::string::npos )
		{
			text = text.substr( index );
		}
	}

	void trim_right( std::string & text )
	{
		size_t index = text.find_last_not_of( " \t" );

		if ( index != std::string::npos )
		{
			text = text.substr( 0, index + 1 );
		}
	}

	void trim( std::string & text )
	{
		trim_left( text );
		trim_right( text );
	}

	std::string getPath( std::string const & fileName )
	{
		std::string normalised( fileName );
		replace( normalised, '/', PATH_SEPARATOR );
		replace( normalised, '\\', PATH_SEPARATOR );
		return normalised.substr( 0, normalised.find_last_of( PATH_SEPARATOR ) );
	}
}
