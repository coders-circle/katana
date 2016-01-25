#pragma once
#include <material/Program.h>


class Material
{
public:
    Material(const std::vector<Shader*>& shaders,
        bool useStdTransforms = true)
        : m_program(shaders, useStdTransforms)
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


#include <texture/Texture.h>


class TestMaterial : public Material
{
public:
    TestMaterial(const std::string& textureFile)
        : Material(std::vector<Shader*> {
            Manager<Shader>::GetShared().Get("test_vs"),
            Manager<Shader>::GetShared().Get("test_fs"),
        }), texture(textureFile)
    {
        m_program.AddUniform("color");
        m_program.AddUniform("diffuseTexture");
    }

    glm::vec4 color;
    Texture texture;

    void SetUniforms()
    {
        m_program.SetUniform("color", color);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture.GetTexture());
        m_program.SetUniform("diffuseTexture", (int)0);
    }
};
