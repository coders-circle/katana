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
    ~Shader()
    {
        glDeleteShader(m_shader);
    }

    GLuint GetShaderObject() const { return m_shader; }

    void AttachTo(GLuint program) const
    {
        glAttachShader(program, m_shader);
    }

    void DetachFrom(GLuint program) const
    {
        glDetachShader(program, m_shader);
    }


private:
    // The shader object
    GLuint m_shader;
};
