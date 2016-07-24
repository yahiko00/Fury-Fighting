#ifndef ___LMP3D_StringUtils_H___
#define ___LMP3D_StringUtils_H___

#include <string>

namespace LMP3D
{
	/**
	@brief
		Replaces toReplace by replacement into text.
	@param[in,out] text
		The source and destination text.
	@param[in] toReplace
		The text to replace.
	@param[in] replacement
		The replacement text.
	*/
	void replace( std::string & text, std::string const & toReplace, std::string const & replacement );
	/**
	@brief
		Removes blank characters (' ', '\t', '\r') from the leftmost part of a text.
	@param[in,out] text
		The source and destination text.
	@return
		The text.
	*/
	std::string & trimLeft( std::string & text );
	/**
	@brief
		Removes blank characters (' ', '\t', '\r') from the rightmost part of a text.
	@param[in,out] text
		The source and destination text.
	@return
		The text.
	*/
	std::string & trimRight( std::string & text );
	/**
	@brief
		Gets the given text with upper case characters replaced by their lower case counterparts.
	@param[in] text
		The source text.
	@return
		The lowered case text.
	*/
	std::string lowerCase( std::string const & text );
	/**
	@brief
		Gets the given text with lower case characters replaced by their upper case counterparts.
	@param[in] text
		The source text.
	@return
		The uppered case text.
	*/
	std::string upperCase( std::string const & text );
	/**
	@brief
		Replaces toReplace by replacement into text.
	@param[in,out] text
		The source and destination text.
	@param[in] toReplace
		The text to replace.
	@param[in] replacement
		The replacement text.
	*/
	inline void replace( std::string & text, char toReplace, char replacement )
	{
		char find[2] = { toReplace, '\0' };
		char replaced[2] = { replacement, '\0' };
		replace( text, find, replaced );
	}
	/**
	@brief
		Replaces toReplace by replacement into text.
	@param[in,out] text
		The source and destination text.
	@param[in] toReplace
		The text to replace.
	@param[in] replacement
		The replacement text.
	*/
	inline void replace( std::string & text, std::string const & toReplace, char replacement )
	{
		char replaced[2] = { replacement, '\0' };
		replace( text, toReplace, replaced );
	}
	/**
	@brief
		Replaces toReplace by replacement into text.
	@param[in,out] text
		The source and destination text.
	@param[in] toReplace
		The text to replace.
	@param[in] replacement
		The replacement text.
	*/
	inline void replace( std::string & text, char toReplace, std::string const & replacement )
	{
		char find[2] = { toReplace, '\0' };
		replace( text, find, replacement );
	}
	/**
	@brief
		Removes blank characters (' ', '\t', '\r') from the leftmost and rightmost parts of a text.
	@param[in,out] text
		The source and destination text.
	@return
		The text.
	*/
	inline std::string & trim( std::string & text )
	{
		return trimLeft( trimRight( text ) );
	}
}

#endif
