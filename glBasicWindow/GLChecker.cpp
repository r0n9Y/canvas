#include "GLChecker.h"
#include <iostream>

void opgl::ClearError()
{
	while (GL_NO_ERROR != glGetError());
}

bool opgl::CheckError(const char* funcName, const char* fileName, const int lineNumber)
{
	GLenum error = GL_NO_ERROR;
	bool hasError = false;
	do
	{
		error = glGetError();
		if(GL_NO_ERROR != error)
		{
			std::cerr << "[GLError]" << std::hex << "0x" << error << std::dec 
				<<"In function: "<< funcName 
				<< " In file: " << fileName 
				<< " @ "<< lineNumber << EOL;
			hasError = true;
		}
	} while (error != GL_NO_ERROR);
	return hasError;
}