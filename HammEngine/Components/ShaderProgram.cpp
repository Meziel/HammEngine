#include "ShaderProgram.h"

#include <fstream>
#include <sstream>
#include <iostream>

#include "../ComponentTypes.h"

namespace GameEngine
{
	std::set<ShaderProgram*> ShaderProgram::shaderPrograms = std::set<ShaderProgram*>();

	ShaderProgram::ShaderProgram(const std::string vertexFilePath, const std::string fragmentFilePath) :
        Component(ComponentTypes::SHADER_PROGRAM),
		vertexFilePath(vertexFilePath),
		fragmentFilePath(fragmentFilePath)
	{
		this->shaderPrograms.insert(this);
		this->shadersCompiled = false;
	}

	ShaderProgram::~ShaderProgram()
	{
		if (program != 0)
		{
			glDeleteProgram(this->program);
		}

		this->shaderPrograms.erase(this);
	}

	void ShaderProgram::compileShaders()
	{
		std::string vertexShaderSource;
		std::string fragmentShaderSource;

		GLuint vertexShader;
		GLuint fragmentShader;

		bool success;

		//get source code from shader files
		vertexShaderSource = this->getShaderSource(vertexFilePath.c_str());
		fragmentShaderSource = this->getShaderSource(fragmentFilePath.c_str());

		//create shaders from source
		success = createShader(GL_VERTEX_SHADER, (GLchar*)(vertexShaderSource.c_str()), &vertexShader);
		if (!success)
		{
			printShaderErrors(vertexShader);
			return;
		}

		success = createShader(GL_FRAGMENT_SHADER, (GLchar*)(fragmentShaderSource.c_str()), &fragmentShader);
		if (!success)
		{
			printShaderErrors(fragmentShader);
			return;
		}

		success = createProgram(vertexShader, fragmentShader);
		if (!success)
		{
			printProgramErrors(this->program);
			return;
		}

		deleteShaders(vertexShader, fragmentShader);

		this->shadersCompiled = true;
	}

	std::string ShaderProgram::getShaderSource(const char* filePath)
	{

		std::string shaderSource;
		std::ifstream shaderFile;
		std::stringstream shaderStream;

		shaderFile.open(filePath);
		if (!shaderFile.is_open())
		{
			std::cout << "Failed to open file " << filePath << std::endl;
		}
		shaderStream << shaderFile.rdbuf();
		shaderFile.close();

		shaderSource = shaderStream.str();

		return shaderSource;
	}

	bool ShaderProgram::createShader(GLenum type, GLchar* source, GLuint* shaderPtr)
	{
		GLuint shader = 0;
		GLint success;

		shader = glCreateShader(type);
		glShaderSource(shader, 1, &source, NULL);
		glCompileShader(shader);

		*shaderPtr = shader;

		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success || shader == 0)
		{
			return false;
		}

		return true;
	}

	bool ShaderProgram::createProgram(GLuint vertexShader, GLuint fragmentShader)
	{

		this->program = 0;
		GLint success;

		this->program = glCreateProgram();
		glAttachShader(this->program, vertexShader);
		glAttachShader(this->program, fragmentShader);
		glLinkProgram(this->program);

		glGetProgramiv(program, GL_LINK_STATUS, &success);
		if (!success || this->program == 0)
		{
			return false;
		}

		return true;
	}

	void ShaderProgram::deleteShaders(GLuint vertexShader, GLuint fragmentShader)
	{

		if (vertexShader != 0)
		{
			glDeleteShader(vertexShader);
		}

		if (fragmentShader != 0)
		{
			glDeleteShader(fragmentShader);
		}

	}

	void ShaderProgram::printShaderErrors(GLuint shader)
	{

		GLchar infoLog[512];

		if (shader == 0)
		{
			std::cout << "Shader creation failed" << std::endl;
			return;
		}

		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		std::cout << "Shader compilation failed" << std::endl << infoLog << std::endl;
	}

	void ShaderProgram::printProgramErrors(GLuint program)
	{

		GLchar infoLog[512];

		if (program == 0)
		{
			std::cout << "Program creation failed" << std::endl;
			return;
		}

		glGetProgramInfoLog(program, 512, NULL, infoLog);
		std::cout << "Program linking falied\n" << infoLog << std::endl;

	}

	GLuint ShaderProgram::getProgram()
	{
		return this->program;
	}

	void ShaderProgram::use()
	{
		if (this->program != 0)
		{
			glUseProgram(this->program);
		}
	}
}