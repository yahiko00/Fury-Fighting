#ifndef ___LMP3D_FileUtils_H___
#define ___LMP3D_FileUtils_H___

#include <string>

namespace LMP3D
{
#if defined( _WIN32 )

	//! The folder separator character.
	static char const PATH_SEPARATOR = '\\';

#else

	//! The folder separator character.
	static char const PATH_SEPARATOR = '/';

#endif

	/**
	@brief
		Retrieves given file's extension.
	@param[in] filePath
		The file path.
	@return
		The file extension.
	*/
	std::string getFileExtension( std::string const & filePath );
	/**
	@brief
		Retrieves given file's parent path.
	@param[in] filePath
		The file path.
	@return
		The file parent path.
	*/
	std::string getFilePath( std::string const & filePath );
	/**
	@brief
		Retrieves given file's name.
	@param[in] filePath
		The file path.
	@param[in] withExtension
		Tells if we want the extension, added to the file name.
	@return
		The file name.
	*/
	std::string getFileName( std::string const & filePath, bool withExtension = false );
	/**
	@return
		The current working directory.
	*/
	std::string getCurrentDirectory();
	/**
	@return
		The datas directory.
	*/
	std::string getDataDirectory();

	/**
	@brief
		Retrieves the given path's parent path.
	@param[in] p_path
		The path.
	@return
		The parent path.
	*/
	std::string getParentPath( std::string const & p_path );
}
/**
@brief
	Concatenates two paths using folder separator.
*@param[in] p_lhs, p_rhs
	The paths to concatenate.
@return
	The concatenated path (p_lhs / p_rhs).
*/
std::string operator/( std::string const & p_lhs, std::string const & p_rhs );

/**
@brief
	Concatenates two paths using folder separator.
*@param[in] p_lhs, p_rhs
	The paths to concatenate.
*@return
	The concatenated path (p_lhs / p_rhs).
*/
inline std::string operator/( std::string const & p_lhs, char const * const p_rhs )
{
	return p_lhs / std::string{ p_rhs };
}

/**
@brief
	Concatenates two paths using folder separator.
*@param[in] p_lhs, p_rhs
	The paths to concatenate.
*@return
	The concatenated path (p_lhs / p_rhs).
*/
inline std::string operator/( char const * const p_lhs, std::string const & p_rhs )
{
	return std::string{ p_lhs } / p_rhs;
}

#endif
