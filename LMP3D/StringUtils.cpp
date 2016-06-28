#include "StringUtils.h"

#include <algorithm>

namespace LMP3D
{
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

	std::string & trimLeft( std::string & text )
	{
		size_t index = text.find_first_not_of( " \t\r" );

		if ( index != std::string::npos )
		{
			text = text.substr( index );
		}

		return text;
	}

	std::string & trimRight( std::string & text )
	{
		size_t index = text.find_last_not_of( " \t\r" );

		if ( index != std::string::npos )
		{
			text = text.substr( 0, index + 1 );
		}

		return text;
	}

	std::string lowerCase( std::string const & text )
	{
		std::string result( text );
		std::transform( result.begin(), result.end(), result.begin(), tolower );
		return result;
	}

	std::string upperCase( std::string const & text )
	{
		std::string result( text );
		std::transform( result.begin(), result.end(), result.begin(), toupper );
		return result;
	}
}
