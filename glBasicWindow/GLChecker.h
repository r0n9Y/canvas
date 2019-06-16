#pragma once

/// Use the OpenGL error checker to detect errors

#include "GLHeaders.h"
#define CHECK_LINE(x) if(x){__debugbreak();}
#define GLCall(x) opgl::ClearError();\
		x;\
		CHECK_LINE(opgl::CheckError(#x, __FILE__, __LINE__))
	
namespace opgl
{
	// The function swollowing all errors and ignoring them
	void ClearError();

	// true: has at leaset one error. false has no error
	bool CheckError(const char* funcName, const char* fileName, const int lineNumber);
} // namespace ogl
