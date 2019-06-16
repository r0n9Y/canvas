//#include <GL/glew.h>
//#include <GLFW/glfw3.h>
#include "GLChecker.h"
#include <iostream>
#include <fstream>
#include <sstream>

enum class ShaderType
{
	NONE = 1,
	VERTEX = 0,
	FRAGMENT = 1,
	MAX,
};
struct ShaderSource
{
	std::string content[(int)ShaderType::MAX];
};

static ShaderSource LoadShader(const std::string & filePath)
{
	std::ifstream stream(filePath);
	std::string line;
	std::stringstream ss[2];
	ShaderType type = ShaderType::NONE;
	while (std::getline(stream, line))
	{
		if (std::string::npos != line.find("ShaderTypeInfo:"))
		{
			if (std::string::npos != line.find("vertex"))
			{
				type = ShaderType::VERTEX;
			}
			else if (std::string::npos != line.find("fragment"))
			{
				type = ShaderType::FRAGMENT;
			}
		}
		else
		{
			ss[(int)type] << line << EOL;
		}
		
	}
	return { ss[0].str(), ss[1].str() };
}

void InitGeometory()
{
	constexpr int NUM_VERTICES = 8;
	float pos[NUM_VERTICES] = {
		-0.5f, -0.5f,
		+0.5f, +0.5f,
		-0.5f, +0.5f,
		+0.5f, -0.5f,
	};

	GLuint vtxid;
	// Vertex info
	glGenBuffers(1, &vtxid);
	glBindBuffer(GL_ARRAY_BUFFER, vtxid);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * NUM_VERTICES, pos, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, (const void*)0);
	glEnableVertexAttribArray(0);

	// Index info
	unsigned short indices[] = {0, 1, 2, 0, 3, 1};
	unsigned idxId;
	glGenBuffers(1, &idxId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, idxId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
}

void InstallShader(const int programId, const int type, const std::string& src)
{
	const char* pSrc = src.c_str();
	auto id = glCreateShader(type);
	glShaderSource(id, 1, &pSrc, nullptr);
	glCompileShader(id);
	// error handling
	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (GL_FALSE == result)
	{
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* info = (char*)alloca(length * sizeof(char));
		glGetShaderInfoLog(id, length, &length, info);
		std::cout << info << EOL;
	}
	glAttachShader(programId, id);
}

const unsigned CreateProgram()
{
	auto source = LoadShader("res/shaders/basic.shader");
	auto pid = glCreateProgram();
	InstallShader(pid, GL_VERTEX_SHADER, source.content[(int)ShaderType::VERTEX]);
	InstallShader(pid, GL_FRAGMENT_SHADER, source.content[(int)ShaderType::FRAGMENT]);
	glLinkProgram(pid);
	glValidateProgram(pid);

	glUseProgram(pid);
	return pid;
}

int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
	{
		std::cout << "unable to initialize glfw" << EOL;
		return -1;
	}

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}
	/* Make the window's context current */
	glfwMakeContextCurrent(window);
	
	if (GLEW_OK != glewInit()) 
	{
		std::cout << "unable to initialize glew" << EOL;
		return -1;
	}
	
	InitGeometory();
	CreateProgram();
	std::cout << "OpenGL version supported by this platform " << glGetString(GL_VERSION) << EOL;
	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		//glDrawArrays(GL_TRIANGLES, 0, 3);
		
		//glDrawElements(GL_TRIANGLES, 61, GL_UNSIGNED_SHORT, 0);
		GLCall(glDrawElements(GL_TRIANGLES, 61, GL_INT, 0));
		
		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}
