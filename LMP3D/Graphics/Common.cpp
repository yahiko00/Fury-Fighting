#include "Common.h"

#include <GL/glew.h>

#include <iostream>

namespace LMP3D
{
	namespace Graphics
	{
		static uint32_t const ErrorCount = 6;

		bool glCheckError( char const * const p_name )
		{
			static char const * const Errors[ErrorCount] =
			{
				"Invalid Enum",
				"Invalid Value",
				"Invalid Operation",
				"Stack Overflow",
				"Stack Underflow",
				"Out Of Memory",
			};

			unsigned int l_error = glGetError();
			bool l_return = l_error == GL_NO_ERROR;

			if ( !l_return )
			{
				l_error -= GL_INVALID_ENUM;
				std::cerr << "Error encountered executing OpenGL function " << p_name << " ";

				if ( l_error < ErrorCount )
				{
					std::cerr << Errors[l_error] << std::endl;
				}
				else
				{
					std::cerr << "Unknow error (" << std::hex << ( l_error + GL_INVALID_ENUM ) << ")" << std::endl;
				}
			}

			return l_return;
		}
	}
}
