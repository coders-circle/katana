#pragma once

#include <stdinc.h>
#include <model/Mesh.h>

class BlockMaterial: public Material
{
public:
    BlockMaterial()
        : Material(std::vector<Shader*> {
            Manager<Shader>::GetShared().Get("test_vs"),
            Manager<Shader>::GetShared().Get("block_fs"),
            //Shader("shaders/vs_block.glsl", GL_VERTEX_SHADER),
            //Shader("shaders/fs_block.glsl", GL_FRAGMENT_SHADER),
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


class Block
{
public:
    Block():
        m_mesh(std::vector<Vertex>{
            Vertex(glm::vec3(-0.4f, -0.4f,  0.4f)),
            Vertex(glm::vec3( 0.4f, -0.4f,  0.4f)),
            Vertex(glm::vec3( 0.4f,  0.4f,  0.4f)),
            Vertex(glm::vec3(-0.4f,  0.4f,  0.4f)),
            Vertex(glm::vec3(-0.4f, -0.4f, -0.4f)),
            Vertex(glm::vec3( 0.4f, -0.4f, -0.4f)),
            Vertex(glm::vec3( 0.4f,  0.4f, -0.4f)),
            Vertex(glm::vec3(-0.4f,  0.4f, -0.4f)),
        }, {
            0, 1, 2, 0, 2, 3,   // front face
            4, 5, 6, 4, 6, 7,   // back face
            1, 5, 6, 1, 6, 2,   // right face
            0, 4, 7, 0, 7, 3,   // left face
            3, 2, 6, 3, 6, 7,   // top face
            0, 1, 5, 0, 5, 4    // bottom face
        })
    {
        m_material.color = glm::vec4(0.3f, 0.4f, 0.3f, 1.0f);
        m_pos = glm::vec3(0, 0, 0);
        m_modelMatrix = glm::translate(glm::mat4(), m_pos);
    }

    void Render(glm::mat4 vp)
    {
        m_mesh.Draw(&m_material, m_modelMatrix, vp);
    }

    void SetPosition(glm::vec3 pos)
    {
        m_pos = pos;
        m_modelMatrix = glm::translate(glm::mat4(), m_pos);
    }

    glm::vec3 GetPosition()
    {
        return m_pos;
    }
protected:
    glm::mat4 m_modelMatrix;
    Mesh m_mesh;
    BlockMaterial m_material;
    glm::vec3 m_pos;
};
