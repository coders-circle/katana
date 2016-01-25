#include <stdinc.h>
#include <material/Program.h>


Program::Program(const std::vector<Shader*>& shaders,
    bool useStdTransforms)
    : m_useStdTransforms(useStdTransforms)
{
    // Create program object
    m_program = glCreateProgram();

    // Attach the shaders and link them
    for (Shader* s : shaders)
        s->AttachTo(m_program);
    glLinkProgram(m_program);

    // Handle error
    GLint status = 0;
    glGetProgramiv(m_program, GL_LINK_STATUS, (int*)&status);
    if (status == GL_FALSE)
    {
        GLint len = 0;
        glGetProgramiv(m_program, GL_INFO_LOG_LENGTH, &len);
        std::vector<GLchar> infoLog(len);
        glGetProgramInfoLog(m_program, len, &len, &infoLog[0]);
        glDeleteProgram(m_program);

        throw ProgramError(std::string(&infoLog[0]));
    }

    // Detach after link
    for (Shader* s: shaders)
        s->DetachFrom(m_program);

    if (useStdTransforms)
        AddStdTransforms();

    glUseProgram(m_program);
}
