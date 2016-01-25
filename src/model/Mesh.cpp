#include <stdinc.h>
#include <model/Mesh.h>


Mesh::Mesh(const std::vector<Vertex>& vertices,
    const std::vector<GLuint>& indices)
{
    // Generate buffers and arrays
    glGenBuffers(1, &m_vbo);
    glGenBuffers(1, &m_ebo);
    glGenVertexArrays(1, &m_vao);

    glBindVertexArray(m_vao);

    // Set vertices data to VBO
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex),
        &vertices[0], GL_STATIC_DRAW);

    // Set indices data to EBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size()
        * sizeof(GLuint), &indices[0], GL_STATIC_DRAW);

    // Vertex Attributes
    // Position
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
        (GLvoid*)offsetof(Vertex, position));
    // Normal
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
        (GLvoid*)offsetof(Vertex, normal));
    // Texture coordinates
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
        (GLvoid*)offsetof(Vertex, texCoords));
    // ...

    glBindVertexArray(0);

    m_numElements = indices.size();
}


void Mesh::Draw(Material* material, const glm::mat4& model, const glm::mat4& vp)
{
    material->Use();

    Program& p = material->GetProgram();
    if (p.DoUseStdTransforms())
    {
        p.SetUniform("mvpMatrix", vp * model);
        p.SetUniform("modelMatrix", model);
    }
    glBindVertexArray(m_vao);
    glDrawElements(GL_TRIANGLES, m_numElements, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}
