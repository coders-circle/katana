#pragma once
#include <Mesh.h>


struct Material
{
    glm::vec4 color;
    std::string texture;
};


class Model
{
public:
    Model(const std::string& path);
    void Save(const std::string& path);

private:
    void LoadNode(aiNode* node);
    void LoadMaterial(const std::string& name, aiMaterial* material);
    void LoadMesh(aiMesh* mesh);

    const aiScene* m_scene;
    std::map<std::string, Material> m_materials;
    std::vector<Mesh> m_meshes;
};
