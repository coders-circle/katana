#pragma once
#include <ecs/Component.h>


// Transformation data that also builds of
// scene hierarchy
class Transform : public ComponentBase<Transform>
{
public:
    Transform(
        const glm::vec3& position = glm::vec3(),
        const glm::quat& rotation = glm::quat(1,0,0,0),
        Transform* parent=0)
        : m_parent(0), m_position(position), m_rotation(rotation),
          m_dirty(true)
    {
        SetParent(parent);
    }

    // Set the parent of this transformation
    void SetParent(Transform* parent);
    // Get parent
    Transform* GetParent() const { return m_parent; }
    // Get children
    Transform* GetChild(int index) const { return m_children[index]; }
    unsigned int GetNumChildren() const { return m_children.size(); }

    // Get local transformation relative to parent
    glm::mat4 GetLocal() const
    {
        return glm::translate(glm::mat4(), m_position)
            * glm::mat4_cast(m_rotation);
    }

    // Get world transformation relative to world
    const glm::mat4& GetWorld()
    {
        if (m_dirty)
        {
            if (m_parent)
                m_transform = m_parent->GetWorld() * GetLocal();
            else
                m_transform = GetLocal();
            m_dirty = false;
        }
        return m_transform;
    }

    // Set transformation
    void SetPosition(const glm::vec3& position)
    {
        m_position = position;
        SetDirty();
    }

    void SetRotation(const glm::quat& rotation)
    {
        m_rotation = rotation;
        SetDirty();
    }

    // Get transformation
    const glm::vec3& GetPosition() const { return m_position; }
    const glm::quat& GetRotation() const { return m_rotation; }

    void SetDirty()
    {
        m_dirty = true;
        for (auto c: m_children)
            c->SetDirty();
    }

    glm::mat4 GetWorldInverse()
    { return glm::affineInverse(GetWorld()); }

private:
    glm::mat4 m_transform;
    glm::vec3 m_position;
    glm::quat m_rotation;

    bool m_dirty;

    Transform* m_parent;
    std::vector<Transform*> m_children;
};
