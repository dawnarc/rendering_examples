#pragma once

#include <map>
#include <string>

#include <glad/glad.h>

#include <glm/glm.hpp>

namespace GLSLShader {
    enum GLSLShaderType {
        VERTEX = GL_VERTEX_SHADER,
        FRAGMENT = GL_FRAGMENT_SHADER,
        GEOMETRY = GL_GEOMETRY_SHADER,
        TESS_CONTROL = GL_TESS_CONTROL_SHADER,
        TESS_EVALUATION = GL_TESS_EVALUATION_SHADER,
        COMPUTE = GL_COMPUTE_SHADER
    };
};

class GLSLProgram
{
public:

    GLSLProgram();

    bool CompileShader(const char* file, GLSLShader::GLSLShaderType ShaderType);

    bool Link();

    bool Use();

    void SetUniform(const char *name, float x, float y, float z);

    void SetUniform(const char *name, const glm::vec4 & v);

    void SetUniform(const char *name, float val);

    void SetUniform(const char *name, const glm::mat3 & m);

    void SetUniform(const char *name, const glm::mat4 & m);

private:

    int GetUniformLocation(const char * name);

private:

    GLuint programHandle;

    bool linked;

    std::map<std::string, int> uniformLocations;
};