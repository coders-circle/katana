#include <stdinc.h>
#include <material/Shader.h>


Shader::Shader(const std::string& filename, GLenum shaderType)
{
    // Create shader object
    m_shader = glCreateShader(shaderType);

    // Set the source
    std::string source = ReadFromFile(filename);
    const char* c_source = source.c_str();
    glShaderSource(m_shader, 1, &c_source, 0);

    // Compile the shader
    glCompileShader(m_shader);

    // Error handling
    GLint success = 0;
    glGetShaderiv(m_shader, GL_COMPILE_STATUS, &success);

    if (success == GL_FALSE)
    {
        GLint logSize = 0;
        glGetShaderiv(m_shader, GL_INFO_LOG_LENGTH, &logSize);
        std::vector<GLchar> errorLog(logSize);
        glGetShaderInfoLog(m_shader, logSize, &logSize, &errorLog[0]);
        glDeleteShader(m_shader);
        
        throw ShaderError(filename, 
            std::string(&errorLog[0]));
    }
}
