#pragma once
#include <material/Material.h>


// Vertex structure
struct Vertex {
    glm::vec3 position;
    // glm::vec3 normal;
    glm::vec2 texCoords;

    Vertex(const glm::vec3& position, const glm::vec2& texCoords)
        : position(position), texCoords(texCoords)
    {}
    Vertex(const glm::vec3& position)
        : position(position)
    {}
};



// Mesh class that can draw itself with given material
class Mesh
{
public:
    Mesh(const std::vector<Vertex>& vertices,
        const std::vector<GLuint>& indices);

    ~Mesh()
    {
        glDeleteVertexArrays(1, &m_vao);
        glDeleteBuffers(1, &m_vbo);
        glDeleteBuffers(1, &m_ebo);
    }

    void Draw(Material* material, const glm::mat4& model, const glm::mat4& vp);

    size_t GetNumTriangles() const { return m_numElements/3; }

private:
    GLuint m_vao, m_vbo, m_ebo, m_numElements;
};
