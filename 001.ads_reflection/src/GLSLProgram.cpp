
#include "GLSLProgram.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using std::string;
using std::ifstream;

GLSLProgram::GLSLProgram() : programHandle(0), linked(false)
{

}

bool GLSLProgram::CompileShader(const char* file, GLSLShader::GLSLShaderType ShaderType)
{
	// Load contents of file
	ifstream inFile(file);
	if (!inFile) 
	{
		fprintf(stderr, "Error opening file: %s\n", file);
		//exit(1);
		return false;
	}

	std::stringstream code;
	code << inFile.rdbuf();
	inFile.close();
	string codeStr(code.str());

	// Create the shader object
	GLuint shaderHandle = glCreateShader(ShaderType);
	if (0 == shaderHandle) 
	{
		fprintf(stderr, "Error creating shader. ShaderType:%d\n", ShaderType);
		//exit(EXIT_FAILURE);
		return false;
	}

	// Load the source code into the shader object
	const GLchar* codeArray[] = { codeStr.c_str() };
	glShaderSource(shaderHandle, 1, codeArray, NULL);

	// Compile the shader
	glCompileShader(shaderHandle);

	// Check compilation status
	GLint result;
	glGetShaderiv(shaderHandle, GL_COMPILE_STATUS, &result);
	if (GL_FALSE == result) 
	{
		fprintf(stderr, "shader compilation failed! ShaderType:%d\n", ShaderType);

		GLint logLen;
		glGetShaderiv(shaderHandle, GL_INFO_LOG_LENGTH, &logLen);

		if (logLen > 0) 
		{
			char * log = (char *)malloc(logLen);

			GLsizei written;
			glGetShaderInfoLog(shaderHandle, logLen, &written, log);

			fprintf(stderr, "Shader log: \n%s", log);

			free(log);
		}

		return false;
	}
	else
	{
		if (!programHandle)
		{
			programHandle = glCreateProgram();
		}

		glAttachShader(programHandle, shaderHandle);
		return true;
	}
}

bool GLSLProgram::Link()
{
	if (linked)
	{
		fprintf(stderr, "program has been linked!");
		return false;
	}

	if (programHandle <= 0)
	{
		fprintf(stderr, "program handle is null!");
		return false;
	}

	linked = true;

	// Link the program
	glLinkProgram(programHandle);

	// Check for successful linking
	GLint status;
	glGetProgramiv(programHandle, GL_LINK_STATUS, &status);
	if (GL_FALSE == status) 
	{

		fprintf(stderr, "Failed to link shader program!\n");

		GLint logLen;
		glGetProgramiv(programHandle, GL_INFO_LOG_LENGTH, &logLen);

		if (logLen > 0) 
		{
			char * log = (char *)malloc(logLen);

			GLsizei written;
			glGetProgramInfoLog(programHandle, logLen, &written, log);

			fprintf(stderr, "Program log: \n%s", log);

			free(log);
		}

		return false;
	}
	else 
	{
		return true;
	}
}

bool GLSLProgram::Use()
{
	if (!linked)
	{
		fprintf(stderr, "program has not been linked!");
		return false;
	}

	if (programHandle <= 0)
	{
		fprintf(stderr, "program handle is null!");
		return false;
	}

	glUseProgram(programHandle);

	return true;
}

void GLSLProgram::SetUniform(const char *name, float x, float y, float z)
{
	GLint loc = GetUniformLocation(name);
	glUniform3f(loc, x, y, z);
}

void GLSLProgram::SetUniform(const char *name, const glm::vec4 & v)
{
	GLint loc = GetUniformLocation(name);
	glUniform4f(loc, v.x, v.y, v.z, v.w);
}

void GLSLProgram::SetUniform(const char *name, float val)
{
	GLint loc = GetUniformLocation(name);
	glUniform1f(loc, val);
}

void GLSLProgram::SetUniform(const char *name, const glm::mat3 & m)
{
	GLint loc = GetUniformLocation(name);
	glUniformMatrix3fv(loc, 1, GL_FALSE, &m[0][0]);
}

void GLSLProgram::SetUniform(const char *name, const glm::mat4 & m)
{
	GLint loc = GetUniformLocation(name);
	glUniformMatrix4fv(loc, 1, GL_FALSE, &m[0][0]);
}

int GLSLProgram::GetUniformLocation(const char * name)
{
	std::map<string, int>::iterator pos;
	pos = uniformLocations.find(name);

	if (pos == uniformLocations.end()) {
		uniformLocations[name] = glGetUniformLocation(programHandle, name);
	}

	return uniformLocations[name];
}