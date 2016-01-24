#pragma once
#include <material/Program.h>


class Material
{
public:
    Material(const std::vector<Shader>& shaders,
        bool useStdTransforms = true)
        :m_program(shaders, useStdTransforms)
    {}

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


class TestMaterial : public Material
{
public:
    TestMaterial() : Material(std::vector<Shader> {
            Shader("shaders/vs_test.glsl", GL_VERTEX_SHADER),
            Shader("shaders/fs_test.glsl", GL_FRAGMENT_SHADER),
        })
    {
        m_program.AddUniform("color");
    }

    glm::vec4 color;

    void SetUniforms()
    {
        m_program.SetUniform("color", color);
    }
};
