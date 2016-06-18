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

	void replace( std::string & input, std::string const & toReplace, std::string const & replacement )
	{
		std::string temp( input );
		std::size_t currentPos = 0;
		std::size_t pos = 0;
		input.clear();

		while ( ( pos = temp.find( toReplace, currentPos ) ) != std::string::npos )
		{
			input.append( temp.substr( currentPos, pos - currentPos ) );
			input.append( replacement );
			currentPos = pos + toReplace.size();
		}

		if ( currentPos != temp.size() )
		{
			input.append( temp.substr( currentPos, pos - currentPos ) );
		}
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

	std::string getPath( std::string const & filePath )
	{
		std::string normalised( filePath );
		replace( normalised, '/', PATH_SEPARATOR );
		replace( normalised, '\\', PATH_SEPARATOR );
		return normalised.substr( 0, normalised.find_last_of( PATH_SEPARATOR ) );
	}

	std::string getFileName( std::string const & filePath, bool withExtension )
	{
		std::string normalised( filePath );
		replace( normalised, '/', PATH_SEPARATOR );
		replace( normalised, '\\', PATH_SEPARATOR );
		normalised = normalised.substr( normalised.find_last_of( PATH_SEPARATOR ) + 1 );

		if ( !withExtension )
		{
			normalised = normalised.substr( 0, normalised.find_last_of( '.' ) );
		}

		return normalised;
	}
}
