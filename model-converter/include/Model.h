#pragma once
#include <Mesh.h>


class Model
{
public:
    Model(const std::string& path);
    void Save(const std::string& path);

private:
    void LoadNode(aiNode* node);
    void LoadMesh(aiMesh* mesh);

    const aiScene* m_scene;
    std::vector<Mesh> m_meshes;
};
