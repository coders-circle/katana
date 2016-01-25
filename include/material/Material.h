#pragma once
#include <material/Program.h>


class Material
{
public:
    Material(const std::vector<Shader*>& shaders,
        bool useStdTransforms = true)
        : m_program(shaders, useStdTransforms)
    {}

    virtual ~Material() {};

    virtual void Use()
    {
        m_program.Use();
        SetUniforms();
    }

    virtual void SetUniforms() = 0;

    Program& GetProgram() { return m_program; }

protected:
    Program m_program;
};
