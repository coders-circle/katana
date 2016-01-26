#include <stdinc.h>
#include <fstream>
#include <material/DiffuseMaterial.h>
#include <model/Model.h>


Model::Model(const std::string& path)
{
    if (!DoesFileExist(path))
        throw FileNotFoundError(path);

    std::ifstream file(path, std::ios::in | std::ios::binary);
    unsigned int num;
    std::string folder = GetFolder(path);

    // Load the materials
    file.read((char*)&num, sizeof(num));
    unsigned int material_sz = num;
    auto& tm = Manager<Texture>::GetShared();
    for (unsigned int i=0; i<material_sz; ++i)
    {
        std::string key = ReadString(file);
        glm::vec4 color;
        file.read((char*)&color[0], sizeof(glm::vec4));

        // Assume texture is in textures folder
        // which is in same folder as the model
        std::string tex = folder + "/textures/" + ReadString(file);
        Texture* t = tm.Get(tex);
        if (!t)
            t = tm.Add(tex, tex);

        m_materials.Add<DiffuseMaterial>(
            path+":"+key, color, t);
    }

    // Load the meshes
    file.read((char*)&num, sizeof(num));
    unsigned int mesh_sz = num;
    for (unsigned int i=0; i<mesh_sz; ++i)
    {
        // Vertices
        file.read((char*)&num, sizeof(num));
        std::vector<Vertex> vs(num);
        file.read((char*)&vs[0], num*sizeof(Vertex));

        // Indices
        file.read((char*)&num, sizeof(num));
        std::vector<GLuint> is(num);
        file.read((char*)&is[0], num*sizeof(GLuint));

        Mesh* m = new Mesh(vs, is);

        // Material
        std::string mat = ReadString(file);
        m->SetMaterial(m_materials.Get(path+":"+mat));
        m_meshes.push_back(m);
    }
}
