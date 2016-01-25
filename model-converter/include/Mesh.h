#pragma once


struct Vertex
{
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoords;
};

struct Texture
{
    std::string filename;
    std::string type;
};


class Mesh
{
public:
    Mesh(const std::vector<Vertex>& vertices,
        const std::vector<unsigned int>& indices)
        : m_vertices(vertices), m_indices(indices)
    {}

    std::vector<Vertex>& GetVertices() { return m_vertices; }
    std::vector<unsigned int>& GetIndices() { return m_indices; }

private:
    std::vector<Vertex> m_vertices;
    std::vector<unsigned int> m_indices;
};
