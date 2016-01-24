#pragma once
#include <material/Shader.h>


// Material error while linking shaders
class ProgramError : public Exception
{
public:
    ProgramError(const std::string& error)
        : Exception("\tError while linking shaders"
            + std::string("\n\tError:\n\t\t") + error)
        {}
};


// Program composed of shaders and their uniforms
class Program
{
public:
    Program(const std::vector<Shader>& shaders,
        bool useStdTransforms=true);
    ~Program()
    {
        glDeleteProgram(m_program);
    }

    GLuint GetProgramObject() const { return m_program; }

    // Add a uniform
    GLint AddUniform(const std::string& uniform_name)
    {
        GLint uniform = glGetUniformLocation(m_program,
            uniform_name.c_str());
        m_uniforms[uniform_name] = uniform;
        return uniform;
    }

    GLint GetUniform(const std::string& uniform_name)
    {
        return m_uniforms[uniform_name];
    }

    void AddStdTransforms()
    {
        AddUniform("mvpMatrix");
        AddUniform("modelMatrix");
    }


    // Set uniform to a value
    void SetUniform(const std::string& uniform, bool boolean)
    { glUniform1i(m_uniforms[uniform], boolean); }
    void SetUniform(const std::string& uniform, GLint integer)
    { glUniform1i(m_uniforms[uniform], integer); }
    void SetUniform(const std::string& uniform, GLfloat number)
    { glUniform1f(m_uniforms[uniform], number); }
    void SetUniform(const std::string& uniform, const glm::mat4& matrix)
    { glUniformMatrix4fv(m_uniforms[uniform], 1, GL_FALSE, glm::value_ptr(matrix)); }
    void SetUniform(const std::string& uniform, const glm::vec4& vector)
    { glUniform4fv(m_uniforms[uniform], 1, glm::value_ptr(vector)); }
    void SetUniform(const std::string& uniform, const glm::vec3& vector)
    { glUniform3fv(m_uniforms[uniform], 1, glm::value_ptr(vector)); }


    // Use program
    void Use() const
    {
        glUseProgram(m_program);
    }


    bool DoUseStdTransforms() const { return m_useStdTransforms; }

private:
    // The GLSL program object
    GLuint m_program;

    // The uniforms
    std::map<std::string, GLint> m_uniforms;

    // Whether the standard transformation uniforms are avialbale
    bool m_useStdTransforms;
};
