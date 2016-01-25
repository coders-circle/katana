#pragma once
#include <material/Material.h>
#include <texture/Texture.h>


class DiffuseMaterial : public Material
{
public:
    DiffuseMaterial(const glm::vec4& color=glm::vec4(1),
        Texture* texture=0)

        : Material(std::vector<Shader*> {
            Manager<Shader>::GetShared().Get("vs_diffuse"),
            Manager<Shader>::GetShared().Get("fs_diffuse"),
        }), color(color), texture(texture)
    {
        m_program.AddUniform("diffuseColor");
        m_program.AddUniform("diffuseTexture");
    }

    glm::vec4 color;
    Texture* texture;

    void SetUniforms()
    {
        static Texture* whiteTexture = 
            Manager<Texture>::GetShared().Get("white");

        m_program.SetUniform("diffuseColor", color);
        glActiveTexture(GL_TEXTURE0);
        if (texture)
            glBindTexture(GL_TEXTURE_2D, texture->GetTexture());
        else
            glBindTexture(GL_TEXTURE_2D, whiteTexture->GetTexture());
        m_program.SetUniform("diffuseTexture", (int)0);
    }
};
