#include "FileUtils.h"

#include "StringUtils.h"

namespace LMP3D
{
	std::string getFileExtension( std::string const & filePath )
	{
		std::string fileName = getFileName( filePath, true );

		if ( !fileName.empty() )
		{
			fileName = fileName.substr( fileName.find_last_of( '.' ) + 1 );
		}

		return fileName;
	}

	std::string getFilePath( std::string const & filePath )
	{
		std::string normalised( filePath );

		if ( !normalised.empty() )
		{
			replace( normalised, '/', PATH_SEPARATOR );
			replace( normalised, '\\', PATH_SEPARATOR );
			normalised = normalised.substr( 0, normalised.find_last_of( PATH_SEPARATOR ) );
		}

		return normalised;
	}

	std::string getFileName( std::string const & filePath, bool withExtension )
	{
		std::string normalised( filePath );

		if ( !normalised.empty() )
		{
			replace( normalised, '/', PATH_SEPARATOR );
			replace( normalised, '\\', PATH_SEPARATOR );
			normalised = normalised.substr( normalised.find_last_of( PATH_SEPARATOR ) + 1 );

			if ( !withExtension && !normalised.empty() )
			{
				normalised = normalised.substr( 0, normalised.find_last_of( '.' ) );
			}
		}

		return normalised;
	}
}
