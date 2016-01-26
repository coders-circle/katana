#include <stdinc.h>
#include <Model.h>


Model::Model(const std::string& path)
    : m_path(path)
{
    // Import the model from the path to a scene
    Assimp::Importer importer;
    m_scene = importer.ReadFile(path,
        aiProcess_Triangulate |
        aiProcess_GenSmoothNormals |
        aiProcess_FlipUVs |
        aiProcess_JoinIdenticalVertices);

    if (!m_scene)
        throw std::runtime_error(
            "Error: Couldn't load scene from file: " + path
        );

    // Load all materials from the scene
    for (unsigned int i=0; i<m_scene->mNumMaterials; ++i)
        LoadMaterial("mat"+std::to_string(i), m_scene->mMaterials[i]);

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


void Model::LoadMaterial(const std::string& name, aiMaterial* material)
{
    Material m;

    // Get diffuse color
    aiColor3D color(0.f, 0.f, 0.f);
    material->Get(AI_MATKEY_COLOR_DIFFUSE, color);
    m.color = glm::vec4(color.r, color.g, color.b, 1.0f);

    // Get texture path
    if (material->GetTextureCount(aiTextureType_DIFFUSE) > 0)
    {
        aiString str;
        material->GetTexture(aiTextureType_DIFFUSE, 0, &str);
        m.texture = GetFilename(str.C_Str());
    }
    else
        m.texture = "";

    m_materials[name] = m;
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


    Mesh m(vertices, indices);
    // Set material
    m.material = "mat" + std::to_string(mesh->mMaterialIndex);

    m_meshes.push_back(m);
}


void Model::Save(const std::string& path)
{
    std::ofstream file(path, std::ios::out | std::ios::binary);
    unsigned int num;

    // Save the materials
    num = m_materials.size();
    file.write((char*)&num, sizeof(num));
    for (auto const& material: m_materials)
    {
        WriteString(file, material.first);
        file.write((char*)&material.second.color[0],
            sizeof(glm::vec4));
        WriteString(file, material.second.texture);

        // Also try and copy the texture
        CopyTexture(path, material.second.texture);
    }

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

        // Material
        WriteString(file, mesh.material);
    }

    // TODO: Save nodes
}


void Model::CopyTexture(const std::string& dest,
    const std::string& filename)
{
    std::string destFolder = GetFolder(dest);
    int status = CreateDirectory(destFolder+"/textures/");

    // TODO: Check status

    // Check if file exists
    std::string folder = GetFolder(m_path);
    if (!DoesFileExist(folder + "/" + filename))
        std::cout << "Couldn't find texture " << filename << std::endl;

    CopyFile(folder+"/"+filename, destFolder+"/textures/"+filename);
}
