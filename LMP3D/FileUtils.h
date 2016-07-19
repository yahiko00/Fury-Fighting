#ifndef ___LMP3D_FileUtils_H___
#define ___LMP3D_FileUtils_H___

#include <string>

namespace LMP3D
{
#if defined( _WIN32 )

	static char const PATH_SEPARATOR = '\\';

#else

	static char const PATH_SEPARATOR = '/';

#endif

	std::string getFileExtension( std::string const & filePath );
	std::string getFilePath( std::string const & filePath );
	std::string getFileName( std::string const & filePath, bool withExtension = false );
	std::string getCurrentDirectory();
	std::string getDataDirectory();
}

#endif
