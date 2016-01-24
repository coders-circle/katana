#pragma once


// Shader compilation exception
class ShaderError : public Exception
{
public:
    ShaderError(const std::string& filename,
        const std::string& error)
        : Exception("\tError while compiling shader"
            + std::string("\n\tFilename: ") + filename
            + std::string("\n\tError:\n\t\t") + error)
        {}
};


// Shader class to handle compilation of shaders
class Shader
{
public:
    Shader(const std::string& filename, GLenum shaderType);

    GLuint GetShaderObject() { return m_shader; }

    void AttachToProgram(GLuint program)
    {
        glAttachShader(program, m_shader);
    }


private:
    GLuint m_shader;
};
