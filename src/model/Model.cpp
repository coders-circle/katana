#include <stdinc.h>
#include <fstream>
#include <model/Model.h>


Model::Model(const std::string& path)
{
    std::ifstream file(path, std::ios::in | std::ios::binary);
    unsigned int num;

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

        // std::cout << "Loaded mesh with "
        //     << vs.size() << " vertices and "
        //     << is.size() << " indices." << std::endl;

        Mesh* m = new Mesh(vs, is);
        m_meshes.push_back(m);
    }
}
