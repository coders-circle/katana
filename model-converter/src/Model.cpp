#include <stdinc.h>
#include <Model.h>


Model::Model(const std::string& path)
{
    // Import the model from the path to a scene
    Assimp::Importer importer;
    m_scene = importer.ReadFile(path,
        aiProcess_Triangulate |
        aiProcess_GenSmoothNormals |
        aiProcess_JoinIdenticalVertices);

    if (!m_scene)
        throw std::runtime_error(
            "Error: Couldn't load scene from file: " + path
        );

    // Load all meshes from the scene
    for (unsigned int i=0; i<m_scene->mNumMeshes; ++i)
        LoadMesh(m_scene->mMeshes[i]);

    // Load the root node
    LoadNode(m_scene->mRootNode);
}


void Model::LoadNode(aiNode* node)
{
    // Load the children nodes
    for (unsigned int i=0; i<node->mNumChildren; ++i)
        LoadNode(node->mChildren[i]);
}


void Model::LoadMesh(aiMesh* mesh)
{
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    // Load the vertices
    vertices.resize(mesh->mNumVertices);
    for (unsigned int i=0; i<mesh->mNumVertices; ++i)
    {
        Vertex& vertex = vertices[i];
        auto aiVertex = mesh->mVertices[i];
        auto aiNormal = mesh->mNormals[i];

        vertex.position = glm::vec3(
            aiVertex.x, aiVertex.y, aiVertex.z);
        vertex.normal = glm::vec3(
            aiNormal.x, aiNormal.y, aiNormal.z);

        if (mesh->mTextureCoords[0])
            vertex.texCoords = glm::vec2(
                mesh->mTextureCoords[0][i].x,
                mesh->mTextureCoords[0][i].y
            );
        else
            vertex.texCoords = glm::vec2(0,0);
    }

    // Load the indices
    for (unsigned int i=0; i<mesh->mNumFaces; ++i)
    {
        auto face = mesh->mFaces[i];
        for (unsigned int j=0; j<face.mNumIndices; ++j)
            indices.push_back(face.mIndices[j]);
    }

    m_meshes.push_back(Mesh(vertices, indices));
}


void Model::Save(const std::string& path)
{
    std::ofstream file(path, std::ios::out | std::ios::binary);
    unsigned int num;

    // Save the meshes
    num = m_meshes.size();
    file.write((char*)&num, sizeof(num));
    for (Mesh& mesh: m_meshes)
    {
        auto vs = mesh.GetVertices();
        auto is = mesh.GetIndices();

        // Vertices
        num = vs.size();
        file.write((char*)&num, sizeof(num));
        file.write((char*)&vs[0], vs.size()*sizeof(Vertex));

        // Indices
        num = is.size();
        file.write((char*)&num, sizeof(num));
        file.write((char*)&is[0], is.size()*sizeof(unsigned int));
    }

    // TODO: Save nodes
}
