#pragma once
#include <model/Mesh.h>


class Model
{
public:
    Model(const std::string& path);
    ~Model()
    {
        for (Mesh* mesh: m_meshes)
            delete mesh;
    }

    void Draw(Material* material, const glm::mat4& model, const glm::mat4& vp)
    {
        for (Mesh* mesh: m_meshes)
            mesh->Draw(material, model, vp);
    }

private:
    std::vector<Mesh*> m_meshes;
};
